

使用django开发，对python manage.py ***命令模式肯定不会陌生。比较常用的有runserver，migrate。。。

本文讲述如何自定义扩展manage命令。 


### 源码分析

manage.py文件是通过django-admin startproject project_name生成的。

#### manage.py的源码
- 首先设置了settings文件，本例中CIServer指的是project_name。
- 其次执行了一个函数django.core.management.execute_from_command_line(sys.argv)，这个函数传入了命令行参数sys.argv

```python
#!/usr/bin/env python
import os
import sys

if __name__ == "__main__":
    os.environ.setdefault("DJANGO_SETTINGS_MODULE", "CIServer.settings")
    try:
        from django.core.management import execute_from_command_line
    except ImportError:
        raise ImportError(
            "Couldn't import Django. Are you sure it's installed and available "
            "on your PATH environment variable? Did you forget to activate a "
            "virtual environment?"
        )
    execute_from_command_line(sys.argv)
```

#### execute_from_command_line

里面调用了ManagementUtility类中的execute方法
```python
def execute_from_command_line(argv=None):
    """
    A simple method that runs a ManagementUtility.
    """
    utility = ManagementUtility(argv)
    utility.execute()
```
在execute中主要是解析了传入的参数sys.argv，并且调用了get_command()

#### get_command
```python
def get_commands():
    """
    Returns a dictionary mapping command names to their callback applications.

    This works by looking for a management.commands package in django.core, and
    in each installed application -- if a commands package exists, all commands
    in that package are registered.

    Core commands are always included. If a settings module has been
    specified, user-defined commands will also be included.

    The dictionary is in the format {command_name: app_name}. Key-value
    pairs from this dictionary can then be used in calls to
    load_command_class(app_name, command_name)

    If a specific version of a command must be loaded (e.g., with the
    startapp command), the instantiated module can be placed in the
    dictionary in place of the application name.

    The dictionary is cached on the first call and reused on subsequent
    calls.
    """
    commands = {name: 'django.core' for name in find_commands(upath(__path__[0]))}

    if not settings.configured:
        return commands

    for app_config in reversed(list(apps.get_app_configs())):
        path = os.path.join(app_config.path, 'management')
        commands.update({name: app_config.name for name in find_commands(path)})

    return commands
```

get_command里遍历所有注册的INSTALLED_APPS路径下的management寻找(find_commands)用户自定义的命令。


#### find_commands
```python
def find_commands(management_dir):
    """
    Given a path to a management directory, returns a list of all the command
    names that are available.

    Returns an empty list if no commands are defined.
    """
    command_dir = os.path.join(management_dir, 'commands')
    # Workaround for a Python 3.2 bug with pkgutil.iter_modules
    sys.path_importer_cache.pop(command_dir, None)
    return [name for _, name, is_pkg in pkgutil.iter_modules([npath(command_dir)])
            if not is_pkg and not name.startswith('_')]

```
可以发现并注册的命令是commands目录下不以"_"开头的文件名。

#### load_command_class

将命令文件***.py中的Command类加载进去。

```python
def load_command_class(app_name, name):
    """
    Given a command name and an application name, returns the Command
    class instance. All errors raised by the import process
    (ImportError, AttributeError) are allowed to propagate.
    """
    module = import_module('%s.management.commands.%s' % (app_name, name))
    return module.Command()
```

#### Command类

Command类要继承BaseCommand类，其中很多方法，一定要实现的是handle方法，handle方法是命令实际执行的代码。
 

##### 如何实现自定义命令

根据上面说的原理，我们只需要在app目录中建立一个目录management，并且在下面建立一个目录叫commands，下面增加一个文件，叫hello.py即可。

要注意一下几点

1）说是目录，其实应该是包，所以在management下面和commands下面都要添加__init__.py。

2）app一定要添加在INSTALLED_APPS中，不然命令加载不到。

应该是这样的

在hello.py中实现命令的具体内容
```python
#-*- coding:utf-8 -*-
from django.core.management.base import BaseCommand, CommandError


class Command(BaseCommand):

    def add_arguments(self, parser):

        parser.add_argument(
            '-n',
            '--name',
            action='store',
            dest='name',
            default='close',
            help='name of author.',
        )

    def handle(self, *args, **options):
        try:
            if options['name']:
                print 'hello world, %s' % options['name']
            
            self.stdout.write(self.style.SUCCESS('命令%s执行成功, 参数为%s' % (__file__, options['name'])))
        except Exception, ex:
            self.stdout.write(self.style.ERROR('命令执行出错'))
```
##### 执行方式
```shell
python manage.py hello -n kangaroo
```

hello world, kangaroo
命令hello.py执行成功，参数为kangaroo
