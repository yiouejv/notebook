### 函数式编程

​    指用一系列函数解决问题

```python
# 示例
        求 1 + 2 + 3 + 4 +...+100的和
        # 方法1
            s = 0
            for x in range(1, 101):
                s += x
            print(s)
        # 方法2
            print(sum(range(1, 101)))
```

### 函数的可重入性

当一个函数的输入一定，则输出必然一定的函数称为可重入函数

说明

​        可重入函数内一定不会访问除局部变量以外的变量

```python
# 示例
        # 可重入函数
        def myadd(x, y):
            return x + y
        print(myadd(100, 200))  # 300

        # 不可重入函数
        y = 200
        def myadd(x):
            return x + y
        print(myadd(y))  # 300
        y = 300
        print(myadd(100))  # 400
```

### 高阶函数

（可用的函数式编程函数）

```
什么是高阶函数？？
        满足下列条件中的一个的函数即为高阶函数
        1. 函数接受一个或多个函数作为参数传入
        2. 函数返回一个函数
```

### python内置的高阶函数

map filter sorted

#### map函数

map(func, *iterable) 

返回一个可迭代对象，此可迭代对象用函数func对可迭代对象iterable中的每一个元素作为参数计算后得新的数据

```python
# 此示例示意map函数的使用
def power2(x):
    return x**2

for x in map(power2, range(1, 10)):
    print(x)  # 1, 4, 9, 16 ... 81
```

**练习**

```
求 1**2 + 2**2 +3**2 +...+ 9**2 的和
求 1**3 + 2**3 +3**3 +...+ 9**3 的和
```

**答案**

```
s = sum((map(lambda x : x**2, range(1, 10))))
print(s)
s = sum((map(lambda x : x**3, range(1, 10))))
print(s)
```

#### filter 函数

```
	语法
        filter(function, iterbale)

    作用
        1. 筛选可迭代对象iterable 中的数据，返回一个可迭代对象，此可迭代对象只返回iterable中符合条件的数据
        2. function将对iterbale中提供的每个数据进行求布尔值，如果为True则保留，否则为False 丢弃数据
```

```
names = ['Tom', 'Jerry', 'Spike', 'Tyke']
l5 = sorted(names, key=lambda s : s[::-1])
print(l5)
```

**练习**

```
	1. 将1-20的偶数用filter生成可迭代对象后，将可迭代对象生成的数据存于列表中
            l = list(filter(lambda x : x%2==0, range(1,21)))
            print(l)
    2. 用filter 函数将1-100之间的所有素数存在列表中
            def isprime(n):
                if n < 2:
                    return False
                for i in range(2, n):
                    if n % i == 0:
                        return False
                return True
            l = list(filter(isprime, range(1,100)))
            print(l)
```

#### sorted 函数

```
	作用
        将原可迭代对象的数据进行排序，生成排序后的列表
    函数参数格式
        sorted(iterable, key=None, reverse=False)
    说明
        iterable 可迭代对象
        【key函数】是用来提供一个值，这个值将作为排序的依据，如果不给出key函数，则用
        原数据的值进行比较和排序
        reverse 标志用来设置是否降序排序
    示例
        l = [5, -2, -4, 0, 3, 1]
        l2 = sorted(l)  # [-4, -2, 0, 1, 3, 5]
        l3 = sorted(l, reverse=True)  # [5, 3, 1, 0, -2, -4]
        l4 = sorted(l, key=abs)   # [0, 1, -2, 3, -4, 5]

        names = ['Tom', 'Jerry', 'Spike', 'Tyke']
        l5 = sorted(names)  # ['Jerry', 'Spike', 'Tom', 'Tyke']

        names = ['Tom', 'Jerry', 'Spike', 'Tyke']
        l5 = sorted(names, key=len)  # ['Tom', 'Tyke', 'Jerry', 'Spike']
```

**练习**

```
	names = ['Tom', 'Jerry', 'Spike', 'Tyke']
    排序的依据为字符串的反序
        'moT' 'yrreJ' 'ekipS' 'ekyT'
    结果为
        ['Spike', 'Tyke', 'Tom', 'Jerry']

        names = ['Tom', 'Jerry', 'Spike', 'Tyke']
        l5 = sorted(names, key=lambda s : s[::-1])
```

