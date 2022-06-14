通过django自带的类库，来加密解密很方便，下面来简单介绍下

### 导入包

```python
from django.contrib.auth.hashers import make_password, check_password
```
从名字就可以看出来他们的作用了。

一个是生成密码，一个是核对密码。

注意：

直接在python命令解释器导入会报错:
```python
django.core.exceptions.ImproperlyConfigured: Requested setting DEFAULT_INDEX_TABLESPACE, but settings are not configured. You must either define the environment variable DJANGO_SETTINGS_MODULE or call settings.configure() before accessing settings.
```

原因:

python启动方式python，会启动交互解释器，需要告诉Django使用哪个设置文件，Django会搜索DJANGO_SETTINGS_MODULE环境变量,它被设置在settings.py中，

需要设置为:multiDatabase.settings

解决方法：用python manage.py shell 来启动命令解释器而不是python，因为python manage.py shell中包含了Django使用哪个settings.py文件


### 生成密码
```python
make_password("123456")
```

得到结果：
```python
u'pbkdf2_sha25615000MAjic3nDGFoi$qbclz+peplspCbRF6uoPZZ42aJIIkMpGt6lQ+Iq8nfQ='
```
另外也可以通过参数来生成密码：
```shell
>>> make_password("123456", None, 'pbkdf2_sha256')
```

### 校验密码

校验就是通过check_password(原始值, 生成的密文)来校验密码的。

```shell
>>> check_password("123456","pbkdf2_sha25615000MAjic3nDGFoi$qbclz+peplspCbRF6uoPZZ42aJIIkMpGt6lQ+Iq8nfQ=")
True
```