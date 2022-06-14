### 迭代器 Iterator

```
什么是迭代器
        迭代器是访问可迭代对象的工具
        迭代器是指用iter(obj)函数返回的对象（实例）
        迭代器可以用next(it)函数获取可迭代对象的数据
```

### 迭代器函数iter 和 next

```
	iter(iterable)
        从可迭代对象中返回一个迭代器，iterable 必须是能提供一个迭代器的对象
    next(iterator)
        从迭代器iterable中获取下一个记录，如果无法获取下一条记录，则触发StopIteration 异常

    说明
        1. 迭代器只能往前取值，不会后退
        2. 用iter 函数可以返回一个可迭代对象的迭代器
```

```python
l = [1, 3, 5, 7]
it = iter(l)  # 让l提供一个能访问自己的迭代器
print(next(it))  # 1 从迭代器中取值，让迭代器去获取l中的一个元素
print(next(it))  # 3 从迭代器中取值，让迭代器去获取l中的一个元素
print(next(it))  # 5 从迭代器中取值，让迭代器去获取l中的一个元素
print(next(it))  # 7 从迭代器中取值，让迭代器去获取l中的一个元素
# next(it)  # StopIteration 异常
```

### 迭代器的用途

用迭代器可以依次访问可迭代对象的数据

```python
l = [2, 3, 5, 7]
for i in l:
	print(l)
    
# 以下用迭代器来访问
l = [2, 3, 5, 7]
    it = iter(l)
    while True:
        try:
            x = next(it)
            print(x)
        except StopIteration:
            break
```

##### **练习**

```
	有一个集合，
    s = {'唐僧', '悟空', '八戒', '沙僧'}

    用for语句来遍历所有元素如下
        for x in s:
            print(x)
        else:
            print('遍历结束')
    将for语句改写为while语句和迭代器实现
```

------

### 生成器 Generator

```
	什么是生成器
        生成器是能够动态提供数据的对象，生成器对象也是可迭代对象（实例）
    生成器有两种
        生成器函数
        生成器表达式
```

**生成器函数的定义**

含有yield语句的函数是生成器函数，此函数被调用将返回一个生成器对象

yield 翻译为（产生或生成）

### yield 语句

```
	语法
        yield表达式
    说明
        yield 用于 def 函数中，目的是将此函数作为生成器函数使用
        yield 用来生成数据， 供迭代器和next(it) 函数使用	
```

```python
# 生成器函数只有在next(it) 函数调用时才会执行，且遇到yield后返回相应的值给next(it)函数
def my_yield():
    print('即将生成2')
    yield 2
    print('即将生成3')
    yield 3
    print('即将生成5')
    yield 5
    print('即将生成7')
    yield 7
    print('生成器生成结束 ')


for i in my_yield():
    print(i)

g = my_yield()  # 调用生成器函数来创建一个生成器，此生成器能生成 2 3 5 7 四个数
it = iter(g)  # 用生成器拿到对应的迭代器
print(next(it))
print(next(it))
```

```python
# 用生成器函数来生成一些列的整数， 0 - n
def myinteger(n):
    i = 0
    while i < n:
        yield i
        i += 1

for x in myinteger(3):
    print(x)

l = [x for x in myinteger(100) if x % 2 == 1]
print(l)
```

### 生成器函数的说明

生成器函数的调用将返回一个生成器对象，生成器对象是一个可迭代对象，通常用来动态生成数据

生成器函数调用return 语句会触发一个StopIteration 异常

**练习**

写一个生成器函数，myeven(start, stop)用来生成start开始带stop结束（不包含）的偶数

### 生成器表达式

```
	语法
        （表达式 for 变量 in 可迭代对象 [if 真值表达式]）
    作用
        用推导式形式创建一个新的生成器
    说明
        if 子句可以省略
    示例
        gen = (x**2 for x in range(1, 5))
        it = iter(gen)
        print(next(it))  # 1
        print(next(it))  # 4
        print(next(it))  # 9
        print(next(it))  # 16
        print(next(it))  # StopIteration
```

##### **练习**

```
	已知有列表
        l = [2, 3, 5, 7]
        1) 写一个生成器函数，让此函数能够动态提供数据，数据为原列表数字的平方加1
        2) 写一个生成器表达式，让此表达式能够动态提供数据，数据为原列表数字的平方加1
        3) 生成一个列表，此列表内的数据是原列表数据的平方加1
```

### 生成器表达式和列表推导式的区别

```python
l = [2, 3, 5, 7]
l2 = [x ** 2 + 1 for x in l]
it = iter(l2)
print(next(it))  # ?

l[1] = 30
print(next(it))  # ??

# 以下是生成器表达式

l = [2, 3, 5, 7]
l2 = (x ** 2 + 1 for x in l)
it = iter(l2)
print(next(it))  # ?

l[1] = 30
print(next(it))  # ??

# 生成器表达式是现用现生成，列表推导式一次性生成静态数据
```

------

### 迭代工具函数

作用是生成一个个性化的可迭代对象

```
zip(iter1 [, iter2[...]])
    返回一个zip对象，此对象用于生成元组，此元组的每个数据来源于参数中的可迭代对象，当最小的可迭代对象不再提供数据时迭代结束

enumerate(iterable [, start])
```

##### zip示例

```python
	numbers = [10086, 10000, 10010, 95588]
    names = ['中国移动', '中国联通', '中国电信']
    for t in zip(numbers, names):
        print(t)
    for No, number, name in zip(range(1, 100), numbers, names):
        print('序号', No, name, '的客服电话是', number)

```

##### enumerate 示例

```python
	names = ['中国移动', '中国联通', '中国电信']
    for t in enumerate(names):
        print(t)

    for t in enumerate(names, 101):
        print(t)

    # 既能得到索引又能得到值
    for index, name in enumerate(name):
        print(index, name)
```

##### **练习**

```
	写一个程序，读入任意行文字，当输入空行时结束，打印带有行号的输入的结果
    如：
        请输入：abdce <回车>
        请输入：hello <回车>
        请输入：bye <回车>
        请输入：<回车>
    输出如下：
        第1行：abdce <回车>
        第2行：hello <回车>
        第3行：bye <回车>
```

