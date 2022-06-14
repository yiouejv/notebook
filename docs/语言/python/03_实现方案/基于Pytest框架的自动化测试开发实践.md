

> Pytest 是 Python 的一种易用、高效和灵活的单元测试框架，可以支持单元测试和功能测试。本文不以介绍 Pytest 工具本身为目的，而是以一个实际的 API 测试项目为例，将 Pytest 的功能应用到实际的测试工程实践中，教大家将 Pytest 用起来。

在开始本文之前，我想跟大家澄清两个概念，一个是测试框架一个是测试工具。很多人容易把他们搞混了，测试框架是诸如 Unittest、Pytest、TestNG 这类，而测试工具指的则是 Selenium、Appium、Jmeter 这类。

测试框架的作用是，帮助我们管理测试用例、执行测试用例、参数化、断言、生成测试报告等基础性工作，让我们将精力用在测试用例的编写上。好的测试框架应该具有很高的扩展性，支持二次开发，并能够支持多种类型的自动化测试。

测试工具的作用是为了完成某一类型的测试，比如 Selenium 用于对 WEB UI 进行自动化测试，Appium 用来对 APP 进行自动化测试，Jmeter 可以用来进行 API 自动化测试和性能测试。另外，Java 语言中 OkHttp 库，Python 语言中的 requests 库，这些 HTTP 的 client 也可以看做是一种 API 测试工具。

澄清了这两个概念，说一下本文的目的。其实网上已经有很多教程，包括官方文档，都是以介绍 Pytest 的功能为出发点，罗列了各种功能的使用方法，大家看完之后会感觉都明白了，但是还是不知道如何与实际项目相结合，真正落地用起来。本文不以介绍 Pytest 工具本身为目的，而是以一个实际的 API 测试项目为例，通过单元测试框架 Pytest 和 Python 的 Requests 库相结合，将 Pytest 功能应用到实际的测试工程实践中，教大家将 Pytest 用起来。

请相信我，使用 Pytest 会让你的测试工作非常高效。


### 01 Pytest 核心功能

在开始使用 Pytest 之前，先来了解一下 Pytest 的核心功能，根据官方网站介绍，它具有如下功能和特点：

- 非常容易上手，入门简单，文档丰富，文档中有很多实例可以参考。
- 能够支持简单的单元测试和复杂的功能测试。
- 支持参数化。
- 能够执行全部测试用例，也可以挑选部分测试用例执行，并能重复执行失败的用例。
- 支持并发执行，还能运行由 nose, unittest 编写的测试用例。
- 方便、简单的断言方式。
- 能够生成标准的 Junit XML 格式的测试结果。
- 具有很多第三方插件，并且可以自定义扩展。
- 方便的和持续集成工具集成。

Pytest 的安装方法与安装其他的 python 软件无异，直接使用 pip 安装即可。

```shell
pip install pytest
```

安装完成后，可以通过下面方式验证是否安装成功：

```shell
pytest --help
```

如果能够输出帮助信息，则表示安装成功了。

接下来，通过开发一个 API 自动化测试项目，详细介绍以上这些功能是如何使用的。

### 02 创建测试项目

先创建一个测试项目目录 api_pytest，为这个项目创建虚拟环境。关于虚拟环境的创建，可以参考这篇文章 <a href="http://blog.580dlw.com/python/%E8%99%9A%E6%8B%9F%E7%8E%AF%E5%A2%83/">虚拟环境</a>。这里我们直接介绍如何使用，执行下面两条命令：

```shell
mkdir api_pytest
cd api_pytest
virtualenv --python=python3 env
```

这样，项目目录和虚拟环境就创建完成了。

应用虚拟环境
```shell
source env/bin/activate
```

接着，安装依赖包，第一个是要安装 pytest，另外本文是以 API 自动化测试为例，因此还要安装一下 HTTP 的 client 包 requests。

```shell
pip install pytest requests
```

现在我们创建一个 data 目录，用来存放测试数据，一个 tests 目录，用来存放测试脚本，一个 config 目录，用来存放配置文件，一个 utils 目录从来存放工具。

```shell
mkdir data tests config utils
```

现在，项目的目录结构应该是如下这样：
```
├── config
├── data
├── env
├── tests
└── utils
```
至此测试项目就创建完成了。接着编写测试用例。

### 03 编写测试用例

在这部分，我们以测试豆瓣电影列表 API 和电影详情 API 为例，编写测试用例。

这两个 API 信息如下：

接口	示例

电影列表	http://api.douban.com/v2/movie/in_theaters?apikey=0df993c66c0c636e29ecbb5344252a4a&start=0&count=10

电影详情	https://api.douban.com/v2/movie/subject/30261964?apikey=0df993c66c0c636e29ecbb5344252a4a

我们先写电影列表 API 的自动化测试用例，设置 3 个校验点：

	1. 验证请求中的 start 与响应中的 start 一致。
	- 验证请求中的 count 与响应中的 count 一致。
	- 验证响应中的 title 是"正在上映的电影-上海"。

在 tests 目录里面，创建个 testintheaters.py 文件，里面编写测试用例，内容如下：

```python
import requests
​
​
class TestInTheaters(object):
    def test_in_theaters(self):
        host = "http://api.douban.com"
        path = "/v2/movie/in_theaters"
        params = {"apikey": "0df993c66c0c636e29ecbb5344252a4a",
                  "start": 0,
                  "count": 10
                  }
        headers = {
            "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.149 Safari/537.36"
        }
        r = requests.request("GET", url=host + path, headers=headers, params=params)
        response = r.json()
        assert response["count"] == params["count"]
        assert response["start"] == params["start"]
        assert response["title"] == "正在上映的电影-上海", "实际的标题是：{}".format(response["title"])
```

你可能会问，这就是测试用例了？这就是基于 Pytest 的测试用例了吗？答案是肯定的。基于 Pytest 编写自动化测试用例，与编写平常的 Python 代码没有任何区别，唯一的区别在于文件名、函数名或者方法名要以 test开头或者test 结尾，类名以 Test 开头。

Pytest 会在 test*.py 或者 *test.py 文件中，寻找 class 外边的 test开头的函数，或者 Test 开头的 class 里面的 test开头的方法，将这些函数和方法作为测试用例来管理。可以通过下面的命令，查看 Pytest 收集到哪些测试用例：

```shell
$ py.test tests/testintheaters.py --collect-only
====================================================== test session starts =======================================================
platform linux -- Python 3.5.2, pytest-5.4.3, py-1.8.1, pluggy-0.13.1
rootdir: /root/api_pytest
collected 1 item                                                                                                                       
<Module tests/testintheaters.py>
  <Class TestInTheaters>
      <Function test_in_theaters>
​
===================================================== no tests ran in 0.10s ======================================================
```

从结果中看到，一共有一条测试用例，TestInTheaters 这个类中的 testintheaters 这个方法。

在 Pytest 中断言使用的是 Python 自带的 assert 语句，非常简单。


### 04 执行测试用例

下面来运行这个测试：
```shell
$ pytest tests/testintheaters.py
========================================================= test session starts ==========================================================
platform linux -- Python 3.5.2, pytest-5.4.3, py-1.8.1, pluggy-0.13.1
rootdir: /root/api_pytest
collected 1 item                                                                                                                       
<Module tests/testintheaters.py>
  <Class TestInTheaters>
      <Function test_in_theaters>

======================================================== no tests ran in 0.08s =========================================================
(env) root@iZ2zec08ev0qz7nmp85ewsZ:~/api_pytest# pytest tests/testintheaters.py 
========================================================= test session starts ==========================================================
platform linux -- Python 3.5.2, pytest-5.4.3, py-1.8.1, pluggy-0.13.1
rootdir: /root/api_pytest
collected 1 item                                                                                                                       

tests/testintheaters.py F                                                                                                        [100%]

=============================================================== FAILURES ===============================================================
___________________________________________________ TestInTheaters.test_in_theaters ____________________________________________________

self = <testintheaters.TestInTheaters object at 0x7f83d108e4e0>

    def test_in_theaters(self):
        host = "http://api.douban.com"
        path = "/v2/movie/in_theaters"
        params = {"apikey": "0df993c66c0c636e29ecbb5344252a4a",
                  "start": 0,
                  "count": 10
                  }
        headers = {
            "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.149 Safari/537.36"
        }
        r = requests.request("GET", url=host + path, headers=headers, params=params)
        response = r.json()
        assert response["count"] == params["count"]
        assert response["start"] == params["start"]
>       assert response["title"] == "正在上映的电影-上海", "实际的标题是：{}".format(response["title"])
E       AssertionError: 实际的标题是：正在上映的电影-北京
E       assert '正在上映的电影-北京' == '正在上映的电影-上海'
E         - 正在上映的电影-上海
E         ?         ^^
E         + 正在上映的电影-北京
E         ?         ^^

tests/testintheaters.py:19: AssertionError
======================================================= short test summary info ========================================================
FAILED tests/testintheaters.py::TestInTheaters::test_in_theaters - AssertionError: 实际的标题是：正在上映的电影-北京
========================================================== 1 failed in 0.51s ===========================================================
```

通过上面的测试输出，我们可以看到该测试过程中，一共收集到了一个测试用例，测试结果是失败的（标记为 F），并且在 FAILURES 部分输出了详细的错误信息，通过这些信息，我们可以分析测试失败的原因。上面测试用例的失败原因是在断言 title 的时候出错了，预期的 title 是“正在上映的电影-上海”，但是实际是“正在上映的电影-北京”，预期和实际的对比非常直观。

执行测试用例的方法还有很多种，都是在 py.test 后面添加不同的参数即可，我在下面罗列了一下：

```shell
$ py.test               # run all tests below current dir
$ py.test test_module.py   # run tests in module
$ py.test somepath      # run all tests below somepath
$ py.test -k stringexpr # only run tests with names that match the
                      # the "string expression", e.g. "MyClass and not method"
                      # will select TestMyClass.test_something
                      # but not TestMyClass.test_method_simple
$ py.test test_module.py::test_func # only run tests that match the "node ID",
                                    # e.g "test_mod.py::test_func" will select
                                    # only test_func in test_mod.py
```

上面这些用法，通过注释很容易理解。在测试执行过程中，这些方法都有机会被用到，最好掌握一下。


### 05 数据与脚本分离

小节的测试用例，将测试数据和测试代码放到了同一个 py 文件中，而且是同一个测试方法中，产生了紧耦合，会导致修改测试数据或测试代码时，可能会相互影响，不利于测试数据和测试脚本的维护。比如，为测试用例添加几组新的测试数据，除了准备测试数据外，还要修改测试代码，降低了测试代码的可维护性。

另外接口测试往往是数据驱动的测试，测试数据和测试代码放到一起也不方便借助 Pytest 做参数化。

将测试代码和测试数据分离已经是测试领域中的共识了。在 data/目录下创建一个用于存放测试数据的 Yaml 文件 testintheaters.yaml，内容如下:

熟悉 Yaml 格式的同学，应该很容易看懂上面测试数据文件的内容。这个测试数据文件中，有一个数组 tests，里面包含的是一条完整的测试数据。一个完整的测试数据由三部分组成：

	- case，表示测试用例名称。
	- http，表示请求对象。
	- expected，表示预期结果。

http 这个请求对象包含了被测接口的所有参数，包括请求方法、请求路径、请求头、请求参数。 expected 表示预期结果，上面的测试数据中，只列出了对请求响应的预期值，实际测试中，还可以列出对数据库的预期值。

测试脚本也要做相应的改造，需要读取 testintheaters.yaml 文件获取请求数据和预期结果，然后通过 requests 发出请求。修改后的测试代码如下：

```python
import requests
import yaml
​
​
def get_test_data(test_data_path):
    case = []  # 存储测试用例名称
    http = []  # 存储请求对象
    expected = []  # 存储预期结果
    with open(test_data_path) as f:
        dat = yaml.load(f.read(), Loader=yaml.SafeLoader)
        test = dat['tests']
        for td in test:
            case.append(td.get('case', ''))
            http.append(td.get('http', {}))
            expected.append(td.get('expected', {}))
    parameters = zip(case, http, expected)
    return case, parameters
​
​
cases, parameters = get_test_data("../data/testintheaters.yaml")
list_params=list(parameters)
​
class TestInTheaters(object):
    def test_in_theaters(self):
        host = "http://api.douban.com"
        r = requests.request(list_params[0][1]["method"],
                             url=host + list_params[0][1]["path"],
                             headers=list_params[0][1]["headers"],
                             params=list_params[0][1]["params"])
        response = r.json()
        assert response["count"] == list_params[0][2]['response']["count"]
        assert response["start"] == list_params[0][2]['response']["start"]
        assert response["total"] == len(response["subjects"])
        assert response["title"] == list_params[0][2]['response']["title"], "实际的标题是：{}".format(response["title"])
```

注意，读取 Yaml 文件，需要安装 PyYAML 包。

测试脚本中定义了一个读取测试数据的函数 gettestdata，通过这个函数从测试数据文件 testintheaters.yaml 中读取到了测试用例名称 case，请求对象 http 和预期结果 expected。这三部分分别是一个列表，通过 zip 将他们压缩到一起。

测试方法 testintheaters 并没有太大变化，只是发送请求所使用的测试数据不是写死的，而是来自于测试数据文件了。

通常情况下，读取测试数据的函数不会定义在测试用例文件中，而是会放到 utils 包中，比如放到 utils/commonlib.py 中。至此，整个项目的目录结构应该是如下所示：

```
├── config
├── data
│   └── testintheaters.yaml
├── env
│   ├── bin
│   ├── lib
│   └── pyvenv.cfg
├── __init__.py
├── __pycache__
│   └── __init__.cpython-35.pyc
├── tests
│   ├── __init__.py
│   ├── __pycache__
│   └── testintheaters.py
└── utils
    ├── commonlib.py
    ├── __init__.py
    └── __pycache__

```

这样，我们修改测试脚本，就修改 testintheaters.py，变更测试数据，就修改 testintheaters.yaml。但是目前看，感觉好像并没有真正看到测试数据和脚本分离的厉害之处，或者更加有价值的地方，那么我们接着往下看。

### 06 参数化

上面我们将测试数据和测试脚本相分离，如果要为测试用例添加更多的测试数据，往 tests 数组中添加更多的同样格式的测试数据即可。这个过程叫作参数化。

参数化的意思是对同一个接口，使用多种不同的输入对其进行测试，以验证是否每一组输入参数都能得到预期结果。Pytest 提供了 pytest.mark.paramtrize 这种方式来进行参数化，我们先看下官方网站提供的介绍 pytest.mark.paramtrize 用法的例子：

```python
# content of tests/test_time.py
import pytest
​
from datetime import datetime, timedelta
​
testdata = [
    (datetime(2001, 12, 12), datetime(2001, 12, 11), timedelta(1)),
    (datetime(2001, 12, 11), datetime(2001, 12, 12), timedelta(-1)),
]
​
​
@pytest.mark.parametrize("a,b,expected", testdata)
def test_timedistance_v0(a, b, expected):
    diff = a - b
    assert diff == expected
```

执行上面的脚本将会得到下面的输出，测试方法 test_timedistance_v0 被执行了两遍，第一遍执行用的测试数据是 testdata 列表中的第一个元组，第二遍执行时用的测试数据是 testdata 列表中的第二个元组。这就是参数化的效果，同一个脚本可以使用不同的输入参数执行测试。

```
============================= test session starts ==============================
platform darwin -- Python 3.7.7, pytest-5.4.1, py-1.8.1, pluggy-0.13.1 -- /Users/chunming.liu/.local/share/virtualenvs/api_pytest-wCozfXSU/bin/python
cachedir: .pytest_cache
rootdir: /Users/chunming.liu/learn/api_pytest/tests
collecting ... collected 2 items
​
test_time.py::test_timedistance_v0[a0-b0-expected0] PASSED    [ 50%]
test_time.py::test_timedistance_v0[a1-b1-expected1] PASSED    [100%]
​
============================== 2 passed in 0.02s ===============================
```

照猫画虎，对我们自己的测试项目中的测试脚本进行如下修改。

```python
import pytest
import requests

from api_pytest.utils.commonlib import get_test_data

cases, list_params = get_test_data("../data/testintheaters.yaml")


class TestInTheaters(object):
    @pytest.mark.parametrize("case,http,expected", list(list_params), ids=cases)
    def test_in_theaters(self, case, http, expected):
        host = "http://api.douban.com"
        r = requests.request(http["method"],
                             url=host + http["path"],
                             headers=http["headers"],
                             params=http["params"])
        response = r.json()
        assert response["count"] == expected['response']["count"]
        assert response["start"] == expected['response']["start"]
        assert response["title"] == expected['response']["title"], "实际的标题是：{}".format(response["title"])

```

在测试方法上面添加了一个装饰器 @pytest.mark.parametrize，装饰器会自动对 list(list_params)解包并赋值给装饰器的第一参数。装饰器的第一个参数中逗号分隔的变量可以作为测试方法的参数，在测试方法内就可以直接获取这些变量的值，利用这些值发起请求和进行断言。装饰器还有一个参数叫 ids，这个值作为测试用例的名称将打印到测试结果中。

在执行修改后的测试脚本前，我们在测试数据文件再增加一组测试数据，现在测试数据文件中，包含了两组测试数据：

```yaml
---
tests:
- case: 验证响应中 start 和 count 与请求中的参数一致
  http:
    method: GET
    path: /v2/movie/in_theaters
    headers:
      User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.149 Safari/537.36
    params:
      apikey: 0df993c66c0c636e29ecbb5344252a4a
      start: 0
      count: 10
  expected:
    response:
      title: 正在上映的电影-上海
      count: 10
      start: 0
- case: 验证响应中 title 是"正在上映的电影-北京"
  http:
    method: GET
    path: /v2/movie/in_theaters
    headers:
      User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.149 Safari/537.36
    params:
      apikey: 0df993c66c0c636e29ecbb5344252a4a
      start: 1
      count: 5
  expected:
    response:
      title: 正在上映的电影-北京
      count: 5
      start: 1
```

现在我们执行一下测试脚本，看看效果：

```shell
============================================================================================================================ test session starts =============================================================================================================================
platform linux -- Python 3.5.2, pytest-5.4.3, py-1.8.1, pluggy-0.13.1
rootdir: /root/api_pytest/tests
collected 2 items                                                                                                                                                                                                                                                            

testintheaters.py F.                                                                                                                                                                                                                                                   [100%]

================================================================================================================================== FAILURES ==================================================================================================================================
_________________________________________________________________ TestInTheaters.test_in_theaters[\u9a8c\u8bc1\u54cd\u5e94\u4e2d start \u548c count \u4e0e\u8bf7\u6c42\u4e2d\u7684\u53c2\u6570\u4e00\u81f4] __________________________________________________________________

self = <api_pytest.tests.testintheaters.TestInTheaters object at 0x7fc79177b048>, case = '验证响应中 start 和 count 与请求中的参数一致'
http = {'headers': {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_5) AppleWebKit/537.36 (KHTML, like Gecko) Chr...T', 'params': {'apikey': '0df993c66c0c636e29ecbb5344252a4a', 'count': 10, 'start': 0}, 'path': '/v2/movie/in_theaters'}
expected = {'response': {'count': 10, 'start': 0, 'title': '正在上映的电影-上海'}}

    @pytest.mark.parametrize("case,http,expected", list(list_params), ids=cases)
    def test_in_theaters(self, case, http, expected):
        host = "http://api.douban.com"
        r = requests.request(http["method"],
                             url=host + http["path"],
                             headers=http["headers"],
                             params=http["params"])
        response = r.json()
        assert response["count"] == expected['response']["count"]
        assert response["start"] == expected['response']["start"]
>       assert response["title"] == expected['response']["title"], "实际的标题是：{}".format(response["title"])
E       AssertionError: 实际的标题是：正在上映的电影-北京
E       assert '正在上映的电影-北京' == '正在上映的电影-上海'
E         - 正在上映的电影-上海
E         ?         ^^
E         + 正在上映的电影-北京
E         ?         ^^

testintheaters.py:20: AssertionError
========================================================================================================================== short test summary info ===========================================================================================================================
FAILED testintheaters.py::TestInTheaters::test_in_theaters[\u9a8c\u8bc1\u54cd\u5e94\u4e2d start \u548c count \u4e0e\u8bf7\u6c42\u4e2d\u7684\u53c2\u6570\u4e00\u81f4] - AssertionError: 实际的标题是：正在上映的电影-北京
======================================================================================================================== 1 failed, 1 passed in 0.63s =========================================================================================================================
```

从结果看，Pytest 收集到了 2 个 items，测试脚本执行了两遍，第一遍执行用第一组测试数据，结果是失败(F)，第二遍执行用第二组测试数据，结果是通过(.)。执行完成后的 summary info 部分，看到了一些 Unicode 编码，这里其实是 ids 的内容，因为是中文，所以默认这里显示 Unicode 编码。为了显示中文，需要在测试项目的根目录下创建一个 Pytest 的配置文件 pytest.ini，在其中添加如下代码：

```shell
[pytest]
disable_test_id_escaping_and_forfeit_all_rights_to_community_support = True
```

再次执行测试脚本，在测试结果的 summary_info 部分，则会显示正确中文内容了。

```shell
FAILED tests/test_in_theaters.py::TestInTheaters::test_in_theaters[验证响应中 start 和 count 与请求中的参数一致] - AssertionError: ...
```

按照这种参数化的方法，如果想修改或者添加测试数据，只需要修改测试数据文件即可。

现在，自动化测试项目的目录结构应该是如下这样：

```
├── config
├── data
│   └── testintheaters.yaml
├── env
│   ├── bin
│   ├── lib
│   └── pyvenv.cfg
├── __init__.py
├── __pycache__
│   └── __init__.cpython-35.pyc
├── tests
│   ├── __init__.py
│   ├── __pycache__
│   ├── pytest.ini
│   └── testintheaters.py
└── utils
    ├── commonlib.py
    ├── __init__.py
    └── __pycache__
```

### 07 测试配置管理

自动化测试代码中，host 是写在测试脚本中的，这种硬编码方式显然是不合适的。这个 host 在不同的测试脚本都会用到，应该放到一个公共的地方来维护。如果需要对其进行修改，那么只需要修改一个地方就可以了。根据我的实践经验，将其放到 config 文件夹中，是比较好的。

除了 host 外，其他与测试环境相关的配置信息也可以放到 config 文件夹中，比如数据库信息、kafka 连接信息等，以及与测试环境相关的基础测试数据，比如测试账号。很多时候，我们会有不同的测试环境，比如 dev 环境、test 环境、stg 环境、prod 环境等。我们可以在 config 文件夹下面创建子目录来区分不同的测试环境。因此 config 文件夹，应该是类似这样的结构：

```
├── config
│   ├── prod
│   │   └── config.yaml
│   └── test
│       └── config.yaml
```

在 config.yaml 中存放不同环境的配置信息，以前面的例子为例，应该是这样：

```yaml
host:
  douban: http://api.douban.com
```

将测试配置信息从脚本中拆分出来，就需要有一种机制将其读取到，才能在测试脚本中使用。Pytest 提供了 fixture 机制，通过它可以在测试执行前执行一些操作，在这里我们利用 fixture 提前读取到配置信息。我们先对官方文档上的例子稍加修改，来介绍 fixture 的使用。请看下面的代码：

```python
import pytest
​
​
@pytest.fixture
def smtp_connection():
    import smtplib
    connection = smtplib.SMTP_SSL("smtp.163.com", 465, timeout=5)
    yield connection
    print("teardown smtp")
    connection.close()
​
​
def test_ehlo(smtp_connection):
    response, msg = smtp_connection.ehlo()
    assert response == 250
    assert 0
```

这段代码中，smtpconnection 被装饰器 @pytest.fixture 装饰，表明它是一个 fixture 函数。这个函数的功能是连接 163 邮箱服务器，返回一个连接对象。当 test_ehlo 的最后一次测试执行完成后，执行 print("teardown smtp")和 connection.close()断开 smtp 连接。

fixture 函数名可以作为测试方法 test_ehlo 的参数，在测试方法内部，使用 fixture 函数名这个变量，就相当于是在使用 fixture 函数的返回值。

回到我们读取测试配置信息的需求上，在自动化测试项目 tests/目录中创建一个文件 conftest.py，定义一个 fixture 函数 env：

```python
@pytest.fixture(scope="session")
def env(request):
    config_path = os.path.join(request.config.rootdir, 
                               "config", 
                               "test", 
                               "config.yaml")
    with open(config_path) as f:
        env_config = yaml.load(f.read(), Loader=yaml.SafeLoader)
    return env_config
```

conftest.py 文件是一个 plugin 文件，里面可以实现 Pytest 提供的 Hook 函数或者自定义的 fixture 函数，这些函数只在 conftest.py 所在目录及其子目录中生效。scope="session"表示这个 fixture 函数的作用域是 session 级别的，在整个测试活动中开始前执行，并且只会被执行一次。除了 session 级别的 fixture 函数，还有 function 级别、class 级别等。

env 函数中有一个参数 request，其实 request 也是一个 fixture 函数。在这里用到了它的 request.config.rootdir 属性，这个属性表示的是 pytest.ini 这个配置文件所在的目录，因为我们的测试项目中 pytest.ini 处于项目的根目录，所以 config_path 的完整路径就是：
```
/root/api_pytest/config/config.yaml
```

将 env 作为参数传入测试方法 testintheaters，将测试方法内的 host 改为 env["host"]["douban"]：

```python
import pytest
import requests

from api_pytest.utils.commonlib import get_test_data

cases, list_params = get_test_data("../data/testintheaters.yaml")


class TestInTheaters(object):
    @pytest.mark.parametrize("case,http,expected", list(list_params), ids=cases)
    def test_in_theaters(self, case, http, expected):
        host = env["host"]["douban"]
        r = requests.request(http["method"],
                             url=host + http["path"],
                             headers=http["headers"],
                             params=http["params"])
        response = r.json()
        assert response["count"] == expected['response']["count"]
        assert response["start"] == expected['response']["start"]
        assert response["title"] == expected['response']["title"], "实际的标题是：{}".format(response["title"])
```

这样就达到了测试配置文件与测试脚本相互分离的效果，如果需要修改 host，只需要修改配置文件即可，测试脚本文件就不用修改了。修改完成后执行测试的方法不变。

上面的 env 函数实现中，有点点小缺憾，就是读取的配置文件是固定的，读取的都是 test 环境的配置信息，我们希望在执行测试时，通过命令行选项，可指定读取哪个环境的配置，以便在不同的测试环境下开展测试。Pytest 提供了一个叫作 pytest_addoption 的 Hook 函数，可以接受命令行选项的参数，写法如下：

```python
def pytest_addoption(parser):
    parser.addoption("--env",
                     action="store",
                     dest="environment",
                     default="test",
                     help="environment: test or prod")
```

pytest_addoption 的含义是，接收命令行选项--env 选项的值，存到 environment 变量中，如果不指定命令行选项，environment 变量默认值是 test。将上面代码也放入 conftest.py 中，并修改 env 函数，将 os.path.join 中的"test"替换为 request.config.getoption("environment")，这样就可以通过命令行选项来控制读取的配置文件了。比如执行 test 环境的测试，可以指定--env test：

```shell
py.test --env test tests/test_in_theaters.py
```

如果不想每次都在命令行上指定--env，还可以将其放入 pytest.ini 中：

```shell
[pytest]
addopts = --env prod
```

命令行上的参数会覆盖 pyest.ini 里面的参数。


### 08 测试的准备与收尾

很多时候，我们需要在测试用例执行前做数据库连接的准备，做测试数据的准备，测试执行后断开数据库连接，清理测试脏数据这些工作。通过 07 小节大家对于通过 env 这个 fixture 函数，如何在测试开始前的开展准备工作有所了解，本小节将介绍更多内容。

@pytest.fixture 函数的 scope 可能的取值有 function，class，module，package 或 session。他们的具体含义如下：

1. function，表示 fixture 函数在测试方法执行前和执行后执行一次。
- class，表示 fixture 函数在测试类执行前和执行后执行一次。
- module，表示 fixture 函数在测试脚本执行前和执行后执行一次。
- package，表示 fixture 函数在测试包（文件夹）中第一个测试用例执行前和最后一个测试用例执行后执行一次。
- session，表示所有测试的最开始和测试结束后执行一次。

通常，数据库连接和断开、测试配置文件的读取等工作，是需要放到 session 级别的 fixture 函数中，因为这些操作针对整个测试活动只需要做一次。而针对测试数据的准备，通常是 function 级别或者 class 级别的，因为测试数据针对不同的测试方法或者测试类往往都不相同。


在 TestInTheaters 测试类中，模拟一个准备和清理测试数据的 fixture 函数 preparation，scope 设置为 function：

```python
@pytest.fixture(scope="function")
    def preparation(self):
        print("在数据库中准备测试数据")
        test_data = "在数据库中准备测试数据"
        yield test_data
        print("清理测试数据")
```

在测试方法中，将 preparation 作为参数，通过下面的命令执行测试：

```
$ py.test -s -q --tb=no tests/test_in_theaters.py
====================================================== test session starts =======================================================
platform darwin -- Python 3.7.7, pytest-5.4.1, py-1.8.1, pluggy-0.13.1
rootdir: /Users/chunming.liu/learn/api_pytest, inifile: pytest.ini
collected 2 items                                                                                                                


tests/test_in_theaters.py 在数据库中准备测试数据
F 清理测试数据
在数据库中准备测试数据
.清理测试数据
​
​
==================================================== short test summary info =====================================================
FAILED tests/test_in_theaters.py::TestInTheaters::test_in_theaters[验证响应中 start 和 count 与请求中的参数一致] - AssertionError: ...
================================================== 1 failed, 1 passed in 0.81s ===================================================
```

通过输出可以看到在每一条测试用例执行前后，各执行了一次“在数据库中准备测试数据”和“清理测试数据”。如果 scope 的值改为 class，执行测试用例的输出信息将是下面这样：

tests/testintheaters.py 在数据库中准备测试数据 F.清理测试数据 在测试类执行前后各执行一次“在数据库中准备测试数据”和“清理测试数据”。

### 09 标记与分组

通过 pytest.mark 可以给测试用例打上标记，常见的应用场景是：针对某些还未实现的功能，将测试用例主动跳过不执行。或者在某些条件下，测试用例跳过不执行。还有可以主动将测试用例标记为失败等等。针对三个场景，pytest 提供了内置的标签，我们通过具体代码来看一下：

```python
import sys
import pytest
​
​
class TestMarks(object):
    @pytest.mark.skip(reason="not implementation")
    def test_the_unknown(self):
        """
        跳过不执行，因为被测逻辑还没有被实现
        """
        assert 0
​
    @pytest.mark.skipif(sys.version_info < (3, 7), reason="requires python3.7 or higher")
    def test_skipif(self):
        """
        低于 python3.7 版本不执行这条测试用例
        :return:
        """
        assert 1
​
    @pytest.mark.xfail
    def test_xfail(self):
        """
        Indicate that you expect it to fail
        这条用例失败时，测试结果被标记为 xfail（expected to fail），并且不打印错误信息。
        这条用例执行成功时，测试结果被标记为 xpassed（unexpectedly passing）
        """
        assert 0
​
    @pytest.mark.xfail(run=False)
    def test_xfail_not_run(self):
        """
        run=False 表示这条用例不用执行
        """
        assert 0
```

下面来运行这个测试：
```
$ py.test -s -q --tb=no tests/test_marks.py
====================================================== test session starts =======================================================
platform darwin -- Python 3.7.7, pytest-5.4.1, py-1.8.1, pluggy-0.13.1
rootdir: /Users/chunming.liu/learn/api_pytest, inifile: pytest.ini
collected 4 items                                                                                                                
​
tests/test_marks.py s.xx
============================================ 1 passed, 1 skipped, 2 xfailed in 0.06s =============================================
```

从结果中可以看到，第一条测试用例 skipped 了，第二条测试用例 passed 了，第三条和第四条测试用例 xfailed 了。

除了内置的标签，还可以自定义标签并加到测试方法上：

```python
@pytest.mark.slow
    def test_slow(self):
        """
        自定义标签
        """
        assert 0
```

这样就可以通过-m 过滤或者反过滤，比如只执行被标记为 slow 的测试用例：
```
$ py.test -s -q --tb=no -m "slow" tests/test_marks.py
$ py.test -s -q --tb=no -m "not slow" tests/test_marks.py
```

对于自定义标签，为了避免出现 PytestUnknownMarkWarning，最好在 pytest.ini 中注册一下：

[pytest]
markers =
    slow: marks tests as slow (deselect with '-m "not slow"')

### 10 并发执行

如果自动化测试用例数量成千上万，那么并发执行它们是个很好的主意，可以加快整体测试用例的执行时间。

pyest 有一个插件 pytest-xdist 可以做到并发执行，安装之后，执行测试用例通过执行-n 参数可以指定并发度，通过 auto 参数自动匹配 CPU 数量作为并发度。并发执行本文的所有测试用例：

```python
$ py.test -s -q --tb=no -n auto tests/
====================================================== test session starts =======================================================
platform darwin -- Python 3.7.7, pytest-5.4.1, py-1.8.1, pluggy-0.13.1
rootdir: /Users/chunming.liu/learn/api_pytest, inifile: pytest.ini
plugins: xdist-1.31.0, forked-1.1.3
gw0 [10] / gw1 [10] / gw2 [10] / gw3 [10] / gw4 [10] / gw5 [10] / gw6 [10] / gw7 [10]
s.FxxF..F.
==================================================== short test summary info =====================================================
FAILED tests/test_marks.py::TestMarks::test_slow - assert 0
FAILED tests/test_smtpsimple.py::test_ehlo - assert 0
FAILED tests/test_in_theaters.py::TestInTheaters::test_in_theaters[验证响应中 start 和 count 与请求中的参数一致] - AssertionError: ...
======================================= 3 failed, 4 passed, 1 skipped, 2 xfailed in 1.91s ========================================
```

可以非常直观的感受到，并发执行比顺序执行快得多。但是并发执行需要注意的是，不同的测试用例之间不要有测试数据的相互干扰，最好不同的测试用例使用不同的测试数据。

这里提一下，pytest 生态中，有很多第三方插件很好用，更多的插件可以在这里 https://pypi.org/search/?q=pytest 查看和搜索，当然我们也可以开发自己的插件。

### 11 测试报告

Pytest 可以方便的生成测试报告，通过指定--junitxml 参数可以生成 XML 格式的测试报告，junitxml 是一种非常通用的标准的测试报告格式，可以用来与持续集成工具等很多工具集成：
```
$ py.test -s -q --junitxml=./report.xml tests/
```

### 12 总结

本文章以实际项目出发，介绍了如何编写测试用例、如何参数化、如何进行测试配置管理、如何进行测试的准备和清理，如何进行并发测试并生成报告。根据本文的介绍，你能够逐步搭建起一套完整的测试项目。

至此，我们的自动化测试项目完整目录结构如下：

```
├── config
│   └── config.yaml
├── data
│   └── testintheaters.yaml
├── env
│   ├── bin
│   ├── lib
│   └── pyvenv.cfg
├── __init__.py
├── tests
│   ├── conftest.py
│   ├── __init__.py
│   ├── pytest.ini
│   ├── testintheaters.py
│   └── test_marks.py
└── utils
    ├── commonlib.py
    ├── __init__.py

```

<img src="../../images/gzh.png" style="width: 100%;">