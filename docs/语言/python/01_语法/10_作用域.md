### 全局变量和局部变量

```
局部变量
        1. 定义在函数内部的变量称为局部变量（函数的形参也是局部变量）
        2. 局部变量只能在函数内部使用
        3. 局部变量在函数调用时才能被创建，在函数调用之后会自动被销毁
全局变量
        1. 定义在函数外部，模块内部的变量称为全局变量
        2. 全局变量所有函数都可以直接访问（但函数内部不能将其赋值）
```

```python
# 此示例示意全局变量和局部变量
a = 100  # 全局变量
b = 200  # 全局变量

def fx(c):  # c是局部变量
    d = 400  # d是局部变量
    print(a, b, c, d)

fx(300)
print(a)
```

**说明**

1. 局部变量只能在其被声明的函数内部访问，而全局变量可以在整个模块范围内访问
2. 在函数内部赋值语句不会对全局变量造成影响

```python
# 示意：
        l = []
        print('id(l) =', id(l))

        def input_number():
            l2 = []
            while True:
                n = int(input('请输入正整数'))
                if n < 0:
                    break
                l2.append(n)
            # l = l2  # 创建局部变量，未改变全局
            # l.extend(l2)  # 根据变量找到列表，改变是列表而不是变量
            # l += l2   # 出错

        input_number()
        print('id(l) =', id(l))
        print(l)
```

### globals() / locals() 函数

- globals()   返回当前全局作用域内变量的字典
- locals()    返回当前局部作用域内变量的字典

```python
a = 1
b = 2
c = 3

def fn(c, d):
    e = 300
    print('locals() 返回：', locals())
    print('globals() 返回：', globals())
    print(globals()['c'])

fn(100, 200)
```

### 函数变量

**函数名变量，它在创建函数时绑定一个函数**

```python
def fn():
    print('函数fn被调用')

f1 = fn
print(f1)  # <function fn at 0xXXXXXXXXXXXXXXXX>
print(fn)  # <function fn at 0xXXXXXXXXXXXXXXXX>
print(f1())  # None
```

**一个函数可以作为另一个函数的实参传递**

```python
# 此示例示意函数作为参数传递给函数

def f1():
    print('hello f1')

def f2():
    print('hello f2')

def fx(fn):
    print(fn)
    fn()  # 调用fn绑定的函数

fx(f1)  # 如何执行
```

```python
# 看懂下面的代码在干什么
        def myinput(fn):
            l = [1, 3, 5, 7, 9]
            return fn(l)

        print(myinput(max))
        print(myinput(min))
        print(myinput(sum))
```

**函数可以返回另一个函数**

```python
# 此示例示意函数返回另一个函数

def get_fuction():
    s = input('请输入您要做的操作：')
    if s == '求最大':
        return max
    elif s == '求最小':
        return min
    elif s == '求和':
        return sum

l = [2, 4, 6, 8 ,10]
f = get_fuction()  # 让函数给我们返回一个操作
print(f(l))
```

**练习**

```
	写一个计算公式的解释执行器
        已知有如下一些函数：
        def myadd(x, y):
            return x + y
        def mysub(x, y)
            return x - y
        def mymul(x, y)
            return x * y

        def get_fun(op):
            .....
        get_fun(op)   函数传入字符串

        在主函数中程序如下：
        def main():
            while True:
                s = input('请输入计算公式')  # 10 加 20
                l = s.split()  # l=['10', '加', '20']
                a = int(l[0])
                b = int(l[2])
                fn = get_fun(l[1])
                print('结果是：', fn(a, b))  # 结果是：30
```

### 函数的嵌套定义

指一个函数里用def 语句来创建另一个函数的情况

```python
	# 示例
        def fn_outter():
            print('fn_outter() 被调用')
            def fn_inner():
                print('fn_inner() 被调用')
            fn_inner()  # 调用嵌套函数fn_inner
            fn_inner()  # 第二次被调用
            print('fn_outter()调用结束')


        fn_outter()  # 调用外层函数
```

### 作用域

作用域也叫名字空间，是访问变量时查找变量名的范围空间

### python3的四个作用域LEGB

```
   作用域                 英文解释                         英文简写
  局部作用域（函数内）    Local(function)                     L
  外部嵌套函数作用域     （包裹）Enclosing function locals       E
  函数定义所在模块作用域   Global(moudle)                          G
  python内置模块的作用域    Builtin(python)                         B
```

```python
v = 100  # 全局作用域

def fun1():
    v = 200  # 外部嵌套函数作用域
    print('fun1.v =', v)

    def fun2():
        v = 300  # 局部作用域
        print('fun2.v =', v)
    fun2()  # 调用fun2

fun1()
print('全局变量v =', v)
```

**详细说明**

1. 在访问变量时，先查找本地变量，然后是包裹此函数外部函数内的变量，之后是全局变量，最后是内建作用域的变量
        即：L --->   E ----->   G ------>  B
2. 在默认情况下，变量名赋值会在当前作用域内创建变量和修改变量

### global语句

```
	作用
        告诉解释执行器，global语句声明的一个或多个变量， 这些变量的作用域为模块级作用域，也称作全局作用域

        全局声明 global 将赋值变量映射到模块文件内部的作用域

    语法
        global 变量名1， 变量名2， ....

    # 示例
        v = 100

        def fn():
            global v  # 告诉解释执行器python3， v 是全局变量， 不是局部变量
            v = 200

        fn()
        print('v =', v)


    说明
        1. 全局变量如果要在函数内部被赋值，则必须经过全局声明（否则被认为是局部变量）
        2. 全局变量在函数内部不经过声明就可以直接访问
        3. 不能先声明局部变量，再用global 声明为全局变量，此做法不符合语法规则
        4. global 变量列表里的变量名不能出现在函数的形参列表里
```

### nonlocal语句

```
	作用
        告诉解释执行器，nonlocal声明的变量不是局部变量，也不是全局变量，而是外部嵌套函数内的变量
    语法
        nonlocal 变量名1, 变量名2 ....

    示例见
        v = 100

        def f1():
            v = 200
            print('f1.v =', v)

            def f2():
                nonlocal v
                v = 300
                print('f2.v =', v)
            f2()

            print('调用f2()后的f1.v =', v)

        f1()
        print('全局的v =', v)

    语法说明
        1. nonlocal 语句只能在被嵌套函数的内部进行使用
        2. 访问nonlocal变量进行赋值操作，将对外部嵌套函数作用域内的变量进行操作
        3. 当有两层或两层以上函数嵌套时，访问nonlocal 变量只对最近一层变量进行操作
        4. nonlocal 语句变量列表里的变量名，不能出现在此函数形参列表中
```

### lambda 表达式

```
	作用
        创建一个匿名函数对象，同def 类似，但不提供函数名
    语法
        lambda [形参名1, 形参名2, ...]:   表达式
    示例见
        # def myadd(x, y):
        #     return x + y

        myadd = lambda x, y : x + y

        print('20 + 30 =', myadd(20, 30))
        print('40 + 50 =', myadd(40, 50))
```

**lambda 表达式的定义规则**

1. lambda 只是一个表达式，它用来创建一个函数
2. 当lambda 表达式调用时，先执行冒号(:) 后的表达式，并返回表达式的结果的引用
3. lambda 表达式创建的函数只能包含一条表达式
4. lambda 比函数简单且可以随时创建和销毁，有利于减少程序的耦合度

**练习**

1. 写一个lambda 表达式，创建一个函数，此函数判断参数 n，的平方加1能否被5整除，如果能返回True, 否则返回False
2. 写一个lambda 表达式，返回两个形参的最大值

### eval, exec 函数

**eval() 函数**

```
	作用
        把一个字符串当成一个表达式来执行，返回表达式执行后的结果
    格式
        eval(source, globals=None, locals=None)
    示例见
        x = 100
        y = 200
        s = 'x + y'

        a = eval(s)  # 解释执行s 字符串， 把表达式的值返回回来
        print(a)  # 300

        # 先从locals（局部作用域）字典中找相应的变量
        # 没有就从globals（全局作用域）字典中找
        b = eval(s, {'x':2, 'y':2}, {'y':2})  # 4
        print(b)
```

**exec 函数**

```
	作用
        把一个字符串当成程序来执行
    格式
        exec(source, globals=None, locals=None)
    示例
        s = '''x = 100
               y = 200
               print('x + y =', x + y)
        '''
        exec(s)
```