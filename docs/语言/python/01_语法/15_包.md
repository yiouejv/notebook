### 包（模块包） Package

```
	包的定义
        包是将模块以文件夹的组织形式进行分组管理的方法
    作用
        将一系列模块进行分类管理，有利于防止命名冲突
        可以在需要时加载一个或部分模块而不是全部模块
    包示例
        __init__.py
        menu.py
        games/
            __init__.py
            contra.py
            supermario.py
            tanks.py
        office/
            __init__.py
            word.py
            excel.py
            
    包内的__init__.py 文件
		__init__.py 是常规包内必须存在的文件
		
	__init__.py 内的__all__列表
		作用
        	用来记录此包中有哪些子包或模块需要导入
        	当用from 包 import * 语句导入模块时，只查找__all__列表中所有模块或子包
    	说明
        	__all__列表只在from xxx import * 导入时起作用
```

### 包的导入

```
	语法规则类似于模块的导入规则
    import 包名[as 包新名]
    import 包名.模块名 [as 模块新名]
    import 包名.子包名.模块名 [as 模块新名]
    ...
    form 包名 import 模块名 [as 模块新名]
    from 包名.子包名 import 模块名 [as 模块新名]
    from 包名.子包名.模块名 import 属性名 [as 属性新名]
    ...
    from 包名 import *
    from 包名.模块名 import *
    ...
```

### import 语句搜索  包的路径和顺序

1. 搜索程序运行时的路径
2. sys.path提供的路径

### 包的相对导入

```
	包的相对导入是指包内模块的相互导入

    语法
        from 相对路径包或模块名，import 属性或模块名
        或
        from 相对路径包或模块名，import *

    相对路径
        在from 和 import 间可以用相对路径
        . 代表当前目录
        .. 代表上一级目录
        ... 代表上二级目录
        .... 以此类推

    注：相对导入时不能超出包的外部
```

