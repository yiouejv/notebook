
<h2>数字（整型/浮点型/复数/布尔型）</h2>

```
字符串 str
列表  list
...

数字
整型数 int
    整型数是不带有小数部分的数据，包括自然数，负数
    如：-5，0，100等

整型字面值的表示方式
    十进制表示
        10， 200，-100，99999999
    八进制表示（0o开头，后跟0~7）
        0o11    (9)
        0o177   (127)
    十六进制表示（0x开头，后跟0-9，A-F,a-f）
        注：a表示10，b表示11。。。。f表示15
        0x11    （17）
        0xff    (255)
    二进制的表示（0b开头，后跟0-1）
        0b111   (7)
        0b1000  (8)

浮点数的表示方式
    浮点数是带有小数部分的数字（小数部分可以是0）
    浮点数的两种表示方式：
        小数形式
            3.14 3.1 3. 0.14 .14
        科学计数法
            小数e/E（正负号）指数
            如： 6.18E-1  (等同于0.618)
                 2.9979e8   (等同于299790000.0)

复数complex
    分为两部分
        实部（real）
        虚部（image）
        注：虚部是以j或J结尾
            复数的字面值表示：
            1j
            (2J)
            1+1J
            1-1j
            (-100+100J)


布尔型数
    用来表示真和假两种状态的类型
        True 表示真（条件满足或成立）
        False 表示假（条件不满足或不成立）
    说明
        True 的值是1
        False 的值是0

空值None
    None是一个表示不存在的特殊对象
    作用： 用来占位/变量解除绑定
```


<h2>运算符和表达式</h2>

```
表达式expression
    由一个数字或数字和运算符组成
    作用
        通常让计算机做一些事情并返回结果
    如 1 + 2 * 3 - 4
算术运算符
    +   加法
    -   减法
    *   乘法
    /   除法
    //  地板除 floordiv
    %   求余
    **  幂运算

    /除法
        得到的数是浮点数，不会丢弃小数部分
        1/3  得 0.333333333333
        8/2  得 4.0

    //地板除
        除的结果去掉小数部分向下取整
        7/3     得2.3333333333333
        7//3        得2
        8//3        得2
        3.25//1.5   得2.0
    %求余
        7%3         得1
        3.25%1.5    得0.25
```


<h2>运算符的优先级</h2>

```
**
*   /   //  %
+   -

括号分组子表达式
    用（）可以将表达式分组，（）内部的表达式先进行计算


混合类型自动升级
    1 + 2.14    返回类型为浮点型  3.14
```

<h2>变量</h2>

变量是关联一个对象的标识符

变量可以绑定一个对象，并可以通过变量名来使用这个对象标识符的命名方法

标识符必须为字母或下划线开头，后跟字母或下划线或数字

说明
    - 不能用python的关键字作变量名
    - python变量名区分大小写

合法的变量示例

    a a1 b bbb _a __ABCD var alb2

不合法的变量名示例

    1a 123 $ABC +a -b @abc

<h2>赋值语句</h2>

```
语法
    变量 = 表达式
    变量名1 = 变量名2 = 变量名3 = 表达式
    变量名1，变量名2，变量名3，... =序列
作用
    创建一个变量或修改一个变量的绑定的对象

说明
    当变量不存在时，创建该变量，同时将变量绑定在这个对象上
    当变量存在时，改变此变量绑定的对象
    一个变量只能绑定一个对象
    两个变量可以同时绑定在一个对象上
示例
    a = 10
    b = 20
```

<h2>Python 中自动化的内存管理</h2>

```
a = 10000
b = 20000
a = a + b   #10000释放，a绑定在30000上
c = a       c和a同时绑定在30000上
```


<h2>Python中 关联/绑定/引用的含义</h2>

在python中，变量没有类型

关联/绑定/引用 都是指一个变量和一个对象的关联关系


<h2>小整数对象池</h2>

CPython 中 整数 -5 至 256永远存在于小整数对象池中，不会释放并可重复使用

<h2>id(x) 函数</h2>

作用：返回一个对象在内存中的地址
