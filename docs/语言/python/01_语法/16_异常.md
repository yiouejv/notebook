### 异常 exception

```
	什么是错误
        错误是指由于逻辑或语法等导致一个程序无法正常执行的问题

    什么是异常
        异常是指程序出错时标识的一种状态
        当异常发生时，程序不会再向下执行，而转去调用此函数的地方待处理此错误并恢复为正常状态

        作用
            用作信号，通知上层调用者有错误产生需要处理
```

**异常处理语句**

- try-except语句
- try-finally语句

### try-except语句

```
	语法
        try:
            可能触发异常的语句
        except 错误类型1 [as 变量1]:
            异常处理语句1
        except 错误类型2 [as 变量2]:
            异常处理语句2
        except(错误类型3，错误类型4):
            异常处理语句3
        ...
        except:
            异常处理语句other
        else:
            未发生异常的语句
        finally:
            最终语句
    作用
        尝试捕获异常（接受异常通知），将程序转为正常状态并继续执行

    语法说明
        as 子句是用于绑定错误对象的变量，可以省略
        except 子句可以有一个或多个，但至少要有一个
        else 子句最多只能有一个，也可以省略不写
        finally 子句最多只能有一个，也可以省略不写
```

```python
def div_apple(n):
    print('%d个苹果您想分给几个人?' % n)
    s = input('请输入人数：')
    cnt = int(s)  # <<- 可能触发ValueError错误进入异常
    result = n / cnt  # <<-- 可能触发ZeroDivisionError 错误
    print('每个人分了', result, '个苹果')

try:
    div_apple(10)
    print('分苹果完成')
except ValueError:
    print('在try的内部语句中发生了值错误，已处理并转为正常状态')
except ZeroDivisionError:
    print('输入人数为0，分苹果失败')


print('程序正常退出')
```

**练习**

    写一个函数，get_score() 来获取学生输入的成绩（0-100的整数）
    如果输入出现异常，则让此函数返回0， 否则返回用户输入的成绩
### try-finally 语句

```
	语法
        try:
            可能触发异常的语句
        finally:
            最终语句
    说明
        finally子句不可以省略
        一定不存在except子句
    作用
        通常用try-finally 语句来做触发异常时必须要处理的事情，无论异常是否发生，finally子句都会被执行
        try-finally 语句不会改变程序的（正常/异常）状态
```

### raise语句

```
	作用
        触发一个错误，让程序进入异常状态，
        发送错误通知给调用者
    语法
        raise 异常类型
        或
        raise 异常对象
        或
        raise 重新出发上一次异常
```

```python
def make_except():
    print('开始')
    # raise ValueError  # 故意发送一个错误通知
    raise ValueError('这是故意制作的一个错误！')
    print('结束')
try:
    make_except()
except ValueError as err:
    print('make_except 发出了ValueError类型的错误，已捕获')
    print(err)

print('程序结束')
```

```python
def make_except():
    raise ValueError('我的一个值错误')

def get_except():
    try:
        make_except()
    except ValueError as err:
        print('错误的值是：', err)
        raise # 重新触发刚收到的错误 等同于raise err

try:
    get_except()
except ValueError as err:
    print('get_except内部发生错误！', err)

print('程序结束')

```

**练习**

写一个函数，get_age() 用来获取一个人的年龄信息

此函数规定用户只能输入1~140之间的整数，如果用户输入其他的数则直接触发ValueError类型的错误来通知调用者

### assert语句

（断言语句）

```
	语法
        assert 真值表达式，错误数据（通常是字符串）
    作用
        当真值表达式为False时，用错误数据创建一个AssertionError类型的错误，并进入异常状态
    等同于
        if 真值表达式 == False:
            raise AssertionError(错误数据)
```

```python
# 此示例示意assert语句的用法
def get_score():
    s = int(input('请输入学生的成绩(0~100)：'))
    # assert 0 <= s <= 100, '成绩超出范围！！！
    # 等同于
    if (0 <= s <= 100) == False:
        raise AssertionError('成绩超出范围')
    return s

try:
    score = get_score()
    print('学生成绩为：', score)
except ValueError:
    print('用户输入的数字不能转为整数...')

except AssertionError:
    print('用户输入的整数不在0~100之间')
```

### 为什么要用异常处理机制

在程序调用层数较深时，向主函数传递错误信息需要层层return返回比较麻烦

