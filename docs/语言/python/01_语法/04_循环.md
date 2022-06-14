### while 语句

```
		作用：
			根据一定条件，重复执行一条语句或多条语句
		语法
			while 真值表达式：
				语句块
			else:
				语句块2
		说明
			1. 先判断真值表达式，为True 或False
			2. 如果为True,则执行语句块1，再回到第一步
			3. 如果为False,则执行语句块2，然后结束此while的执行
			4. else 子句部分可以省略（类似if）
		注意事项
			要控制循环真值表达式的值来防止死循环
			通常用真值表达式内的循环变量来控制循环条件
			通常在循环语句块内改变循环变量来控制循环次数和变量走向
		循环嵌套
			while语句本身是语句，和其他语句一样，可以嵌套在任何符合语句中
			示例
				while 真值表达式：
					...
					while 真值表达式2:
						...
					else:
						...
				else:
					...
```

### break 语句

```
	作用
		用于循环语句中（while， for语句）中，用来终止当前循环语句的执行
	语法
		break
	说明
		1. 当break 语句执行后，此循环语句break 后的语句将不再执行
		2. break 语句通常和if 语句组合使用
		3. break 语句终止循环时else 字句将不再执行
		4. break 语句只能终止当前循环语句的执行，如果有循环嵌套，不会跳出外层循环
```

```python
# ecoding = utf-8
i = 1
while i <= 6:
    print('循环开始时：', i)
    if i == 3:
        break
    print('循环结束时：', i)
    i += 1
print('-------------程序退出---------')
```

### 死循环

- 死循环是指条件一直成立的循环，
- 死循环通常用break语句来终止循环
- 死循环的else子句永远不会执行

```python
# 循环输入字符串，当输入'quit()' 结束输入
# 将每次输入的内容打印在屏幕上
while True:
    s = input('请输入：>>>')
    if s == 'quit()':
        break
    print(s)
else:
    print('else 子句永远不会执行')

```

### for 循环

```
	作用
		用来遍历可迭代对象的数据元素
			可迭代对象是指能依次获取数据元素的对象
	可迭代对象包括：
		字符串（str）
		列表 (list)
		元组 （tuple）
	语法：
		for 变量 in 可迭代对象：
			语句块1
		else:
			语句块2
```

```python
s = 'ABCD'
for ch in s:
    print('ch>>>', ch)
```

**for 语法说明**

else 子句部分可以省略, 当在循环内部用break 终止循环时，else 子句部分不会执行

```python
# 输入一段字符串，判断这个字符串内是否有'H'这个字符，并打印结果
s = input('输入字符串：')
for ch in s:
    if ch == 'H':
        print(s, '有H字符')
        break
else:
    print(s, '没有H字符')
```

### range 函数

```
	range(stop)   用来生成0 - stop区间内的整数，直到stop为止（不包含stop）
	range(start, stop[,step])    用来生成start ~ stop区间内的整数，直到stop为止
					每次生成整数后移动 step
	格式详见
		>>> help(range)

	作用
		用来创建一个生成一系列整数的可迭代对象（也叫整数序列生成器）
	说明
		range返回的对象可以有for 语句来进行依次迭代访问取出其中的整数
	示例
		range(4)	#生成0 1 2 3
		range(3 ,6)	#生成 3 4 5
		range(1, 10, 2)	#生成 1 3 5 7 9
		range(5, 0, -2) #生成 5 3 1
		range(4, 0)	#空

```

### for 语句变量可能不被创建的问题

```
	for i in range(4,0):
		print(i)
	print('绑定', i)    # 报错

	for i in range(0,4):
		print(i)
	print('绑定', i)    # 3
```

### for 语句注意事项

```python
i = 6
for x in range(1, i):  # for x in range(1, 6)
    print('x =', x, 'i =', i)
    i -= 1

# 请问打印结果是什么？
```

### continue 语句

```
	作用
		用于循环语句（while for）中，不再执行本次循环continue
		之后的语句，重新开始一次新的循环
	语法
		continue
	说明
		1. 在while语句中执行continue，将会直接跳到while语句的真值表达式处
		重新判断循环条件
		2. 在for 语句中执行continue 语句，将会从可迭代对象中取下一个元素，
		绑定变量后再次进行循环
```

```python
# 此示例示意continue 语句的用法
for x in range(5):
    if x == 2 or x == 3:
        continue
    print(x)
    
# 打印10以内的奇数
for n in range(10):
    if n % 2 == 0:  # 是偶数，跳过输出
        continue
    print(n)
```

```python
#此示例示意在while 中使用continue 语句

# 略过2
x = -1
while x < 5:
    x += 1
    if x == 2:
        continue
    print(x)
```

