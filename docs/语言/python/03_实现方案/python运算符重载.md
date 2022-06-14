
### 运算符重载
```
什么是运算符重载
        让自定义的类生成的对象（实例）， 能够使用运算符进行操作
    作用
        1. 让自定义类的实例对象像内建函数一样进行运算符的操作
        2. 让程序简洁易读
        3. 让自定义对象将运算符赋予新的规则
```

### 算术运算符的重载
```
    方法名                     运算符和表达式             说明
    __add__(self, rhs)          self + rhs              加法
    __sub__(self, rhs)          self - rhs              减法
    __mul__(self, rhs)          self * rhs              乘法
    __truediv__(self, rhs)      self / rhs              除法
    __floordiv__(self, rhs)     self // rhs             地板法
    __mod__(self, rhs)          self % rhs              取模（求余）
    __pow__(self, rhs)          self ** rhs             幂运算

    rhs (right hand side)  右手边

    说明
        运算符重载方法的参数已经有固定的含义，不建议改变原有的运算符的含义及参数的意义

    二元运算符的重载方法的格式：
        def __xxx__(self, rhs):
            语句块
```
```python
# 此示例示意运算符的重载方法
class MyNumber:
    def __init__(self, v):
        self.data = v

    def __repr__(self):
        return 'MyNumber(%d)' % self.data

    def __add__(self, rhs):
        '''此方法用来制定self + rhs 的规则'''
        v = self.data + rhs.data
        return MyNumber(v)  # 用v创建一个新的对象返回给调用者

    def __sub__(self, rhs):
        v = self.data - rhs.data
        return MyNumber(v)

n1 = MyNumber(100)
n2 = MyNumber(200)
n3 = n1 + n2  # 等同于 n3 = n1.__add__(n2)
print(n3)

n4 = n3 - n2
print('n4 =', n4)
```
##### 练习
```python
# 实现两个自定义列表的想加
class MyList:
    def __init__(self, iterable=()):
        self.data = list(iterable)

    ... 以下自己实现

l1 = MyList([1, 2, 3])
l2 = MyList([4, 5, 6])
l3 = l1 + l2
print(l3)  # MyList([1, 2, 3, 4, 5, 6])
l4 = l2 + l1
print(l4)  # MyList([4, 5, 6, 1, 2, 3])
# 试想能否实现以下操作
    l5 = l1 * 3
    print(l5)  # MyList([1, 2, 3, 1, 2, 3, 1, 2, 3])
```

### 反向运算符的重载
```
    当运算符的左侧为内建类型时，右侧为自定义的类型进行的算术运算符运算时会出现TypeError错误，
    因无法修改内建类型的代码实现运算的重载，此时需要使用反向算术运算符重载

反向算术运算符的重载
    方法名                     运算符和表达式             说明
    __radd__(self, lhs)         lhs + self              加法
    __rsub__(self, lhs)         lhs - self              减法
    __rmul__(self, lhs)         lhs * self              乘法
    __rtruediv__(self, lhs)     lhs /  self             除法
    __rfloordiv__(self, lhs)    lhs // self             地板法
    __rmod__(self, lhs)         lhs %  self             取模（求余）
    __rpow__(self, lhs)         lhs ** self             幂运算


示例见
    exercise_add_list.py


复合赋值算术运算符的重载
    以复合赋值算术运算符 x += y 为例， 此运算符会优先调用 x.__iadd__(y) 方法，如果没有__iadd__方法时
    将会复合赋值拆解为： x = x + y 然后调用 x = x.__add__(y)方法，如果再不存在则会触发TypeError类型的错误异常


复合算术运算符的重载
    方法名                     运算符和表达式             说明
    __iadd__(self, rhs)          self += rhs              加法
    __isub__(self, rhs)          self -= rhs              减法
    __imul__(self, rhs)          self *= rhs              乘法
    __itruediv__(self, rhs)      self /= rhs              除法
    __ifloordiv__(self, rhs)     self //= rhs             地板法
    __imod__(self, rhs)          self %= rhs              取模（求余）
    __ipow__(self, rhs)          self **= rhs             幂运算


比较运算符的重载
    方法名                     运算符和表达式             说明
    __lt__(self, rhs)          self < rhs             小于                little than
    __le__(self, rhs)          self <= rhs            小于等于             little equal

    __gt__(self, rhs)          self > rhs             大于                great than
    __ge__(self, rhs)          self >= rhs            大于等于             great equal

    __eq__(self, rhs)          self == rhs            等于                 equal
    __ne__(self, rhs)          self != rhs            不等于               not equal
    注： 比较运算符通常返回布尔值 True 或 False


位相关运算符重载
    方法名                     运算符和表达式             说明
    __and__(self, rhs)           self & rhs             位与
    __or__(self, rhs)            self | rhs             位或
    __xor__(self, rhs)           self ^ rhs             位异或
    __lshift__(self, rhs)        self << rhs            左移
    __rshift__(self, rhs)        self >> rhs            右移


反向运算符重载
    方法名                     运算符和表达式             说明
    __rand__(self, lhs)           lhs & self            位与
    __ror__(self, lhs)            lhs | self            位或
    __rxor__(self, lhs)           lhs ^ self            位异或
    __rlshift__(self, lhs)        lhs << self           左移
    __rrshift__(self, lhs)        lhs >> self           右移


复合赋值位相关运算符重载
    __iand__(self, rhs)           self &= rhs             位与
    __ior__(self, rhs)            self |= rhs             位或
    __ixor__(self, rhs)           self ^= rhs             位异或
    __ilshift__(self, rhs)        self <<= rhs            左移
    __irshift__(self, rhs)        self >>= rhs            右移


一元运算符的重载
    方法名                     运算符和表达式             说明
    __neg__(self)               -self                    负号
    __pos__(self)               +self                    正号
    __invert__(self)            ~self                    取反

    语法
        class 类名:
            def __xxx__(self):
                ...

    示例见
        my_list.py


二元运算符的重载
    in / not in 运算符重载
    格式
        def __contains__(self, e):
            语句块
    注：in / not in 返回布尔值 True / False
    当重载了__contains__后， in 和 not in 运算符都可用
    not in 运算符的返回值与in 相反

    示例见
        my_list2.py

索引和切片运算符的重载方法
    方法名                     运算符和表达式             说明
    __getitem__(self, item)      x = self[item]        索引/切片 取值
    __setitem__(self, item, v)   self[item] = v        索引/切片 赋值
    __delitem__(self, item)      del self[item]        del语句删除 索引/切片

    作用
        让自定义的类型的对象能够支持索引和切片操作

slice 构造函数
    作用
        用于创建一个slice 对象，此对象用于切片操作的传值
    格式
        slice(start=None, stop=None, step=None)

    slice对象的实例属性
        start 切片的起始值  默认为None
        stop  切片的终止值  默认为None
        step  切片的步长    默认为None

特性属性 @property
    实现其他语言所拥有的getter 和 setter 功能

    作用
        用来模拟一个属性
        通过@property 装饰器，可以对模拟属性的赋值和取值加以控制
    实例见
        property.py
```