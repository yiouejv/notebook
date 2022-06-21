


re模块

### compile(pattern, flags=0)

```
功能：
    生成正则表达式对象
参数
    pattern  正则表达式
    flags  功能标志位，丰富正则表达式的匹配功能， 默认为0
返回值
    返回正则表达式对象
```


### re.findall(pattern, string, flags)

```
功能
    查找正则匹配内容
参数
    pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回匹配到的内容
    如果正则有子组，则之返回子组匹配到的内容
```

### regex.findall(string, pos, endpos)

```
功能
    查找正则匹配内容
参数
    string  目标字符串
    pos 匹配目标的起始位置
    endpos 匹配目标的终止位置
返回值
    返回匹配到的内容
    如果正则有子组，则之返回子组匹配到的内容
```

### re.split(pattern, string, flags=0)

```
功能：
    根据正则表达式匹配的内容切割字符串
参数
   pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回列表，列表中为切割的内容
```

### re.sub(pattern, replaceStr, string, max, flags=0)

```
功能：
    替换正则匹配到的目标字串部分
参数
   pattern 正则表达式
   replaceStr  要替换的内容
   string  目标字符串
   max 最多替换几处
   flags  标志位
返回值
    返回替换后的字符串
```

### re.subn

```
功能、参数和sub一样
返回值
    """Return a 2-tuple containing (new_string, number).
```

### re.finditer(pattern, string, flags=0)

```
功能
    查找正则匹配内容
参数
    pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回一个迭代对象，迭代到的内容是一个match对象
```

### re.fullmatch(pattern, string, flags=0):

```
功能
    完全匹配一个字符串
参数
    pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回一个match对象，如果没有匹配返回None
```

### re.match(pattern, string, flags=0):

```
功能
    从开头位置匹配一个字符串
参数
    pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回一个match对象，如果没有匹配返回None
```

### re.search(pattern, string, flags=0)

```
功能
   匹配一个字符串, 只匹配第一处
参数
    pattern 正则表达式
    string  目标字符串
    flags  标志位
返回值
    返回一个match对象
    如果没有匹配返回None

compile 对象属性
    flags: 标志位
    pattern： 正则表达式
    groups: 子组个数
    groupindex: 获取捕获组字典，键为组名，值为第几组
```


作业

1. 熟悉元字符使用
2. 使用complie对象调用正则表达式方法
3. 读取一个文本，

        × 分别匹配文本中所有的以大写字母开头的单词，包含特殊字符不算

        × 数字， 包括整数，小数，负数，分数，百分数


### match 对象属性

```
属性
    pos
    endpos
    re
    lastgroup
    lastindex

方法
    span()
    start()  匹配内容的开始位置
    end()  匹配内容的结束位置
    group()
        获取match对象获取的内容
        参数：
            默认为0, 表示获取正则匹配的内容
            如果为序列号或者为子组名则为对应的子组匹配到的内容。
        返回值
            匹配到的字符串
    groupdict()
    groups()
例子：
    match.py
```


### flags 参数的使用

```
re.compile    re.findall()   re.search()    re.match()
re.finditer()  re.fullmatch()  re.sub()   re.split()

作用
    辅助正则表达式，丰富匹配结果
I == IGNORECASE    匹配时忽略字母的大小写
S == DOTALL        作用于元字符. 让点可以匹配换行
M == MULTILINE     作用于^  $, 使其可以匹配每一行开头结尾位置
X == VERBOSE（冗长的）       可以给正则添加注释

使用多个标识位使用按位或链接
    re.I | re.S
```
