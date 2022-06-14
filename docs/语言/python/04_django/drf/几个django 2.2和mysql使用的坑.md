###几个django 2.2和mysql使用的坑

可能是由于Django使用的MySQLdb库对Python3不支持，我们用采用了PyMySQL库来代替，导致出现各种坑，特别是执行以下2条命令的是时候：

```
python manage.py makemigrations
or
python manage.py inspectdb
```

第一个坑（提示你的mysqlclient版本过低）
无聊你是否执行pip install mysqlclient安装的最新版的，都抛出：

```
django.core.exceptions.ImproperlyConfigured: mysqlclient 1.3.3 or newer is required; you have 0.7.11.None
```

MD，LZ看到这错误太想骂人了，没办法采取网上的方法，注释大法！

找到Python安装路劲下的Python36-32\Lib\site-packages\django\db\backends\mysql\base.py文件

将文件中的如下代码注释（可能需先关闭pycharm IDE）

```
if version < (1, 3, 3):
    raise ImproperlyConfigured("mysqlclient 1.3.3 or newer is required; you have %s" % Database.__version__)
```

第二个坑（str类型没有decode方法）
对对对，py3默认str是unicode编码，通过encode方法编码成bytes类型，后者才有decode解码方法。
提示错误来源：Python36\lib\site-packages\django\db\backends\mysql\operations.py", line 149, in last_executed_query

这里网上一搜一堆的把encode改成decode方法，我靠，这谁的脑洞无敌了
源方法内容（pip安装的django 2.2.1原封不动的内容）：

    def last_executed_query(self, cursor, sql, params):
        # With MySQLdb, cursor objects have an (undocumented) "_executed"
        # attribute where the exact query sent to the database is saved.
        # See MySQLdb/cursors.py in the source distribution.
        query = getattr(cursor, '_executed', None)
        if query is not None:
            query = query.decode(errors='replace')
        return query
通过print大法输出query结果，内容为

SELECT @@SQL_AUTO_IS_NULL

数据类型为str
这里网上还有注释大法，LZ不知道注释了if的后遗症是啥有没有影响，于是也没采纳。
于是我去django的github去翻这个文件这个方法的最新/历史版本，结果最新master分支内容如下：

    def last_executed_query(self, cursor, sql, params):
        # With MySQLdb, cursor objects have an (undocumented) "_executed"
        # attribute where the exact query sent to the database is saved.
        # See MySQLdb/cursors.py in the source distribution.
        # MySQLdb returns string, PyMySQL bytes.
        return force_str(getattr(cursor, '_executed', None), errors='replace')
看函数名，应该是强制去把SQL转换成str了
我靠！！！这尼玛官网2.2.1/2.2.2(当前最新版)的包不是害人么，记得该文件上面引入下这个方法

```
from django.utils.encoding import force_str
```

然后再执行managa.py命令，可以了
