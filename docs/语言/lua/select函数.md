# select函数

# 前言

今天这个函数看到的时候，第一印象就是想到了c语言中大名鼎鼎的`select`函数，因为他们函数名是一样的，并且lua也是用c语言实现的，所以我认为这个函数跟那个是相同的，可是转念一想lua好像没有什么和网络相关的函数，然后查了一下这个函数的定义，发现这个函数真的就是字面的意思，起到一个选择的作用，我们一起来看一下函数的用法。

# 内容

select()

- 原型：select(index, ···)
- 解释： 如果 `index` 是个数字， 那么返回参数中第 `index` 个之后的部分； 负的数字会从后向前索引（-1 指最后一个参数）。 否则，`index` 必须是字符串 `"#"`， 此时 `select` 返回参数的个数。 

------

## 示例代码

```go
-- 先来试试数字索引
print("\nthe number index result:")
print(select(2, 'b', 'c', 'd', 'e'));

-- 无效的索引
print("\nthe number index of invalid result:")
print(select(20000, 'b', 'c', 'd', 'e'));

-- 字符串#索引
print("\nthe '#' index of invalid result:")
print(select('#', 'b', 'c', 'd', 'e'));


-- 再来看一个常用的例子
function print_multi_argv(...)
    print("\narg list is")
    for i = 1, select('#', ...) do      -- get the count of the params  
        local cur_arg = select(i, ...); -- select the param  
        print(cur_arg);
    end  
end

-- 试验一下打印多个参数
print_multi_argv(1, 2, 3, 'a', 'b', 'f', 't')
```

- 运行结果

```lua
the number index result:
c	d	e

the number index of invalid result:


the '#' index of invalid result:
4

arg list is
1
2
3
a
b
f
t

```