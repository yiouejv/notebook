# 错误处理 pcall & xpcall

## pcall

pcall 指的是 `protected call` 类似其它语言里的 `try-catch`, 使用pcall 调用函数，如果函数 f 中发生了错误， 它并不会抛出一个错误，而是返回错误的状态, 为被执行函数提供一个保护模式，保证程序不会意外终止

语法

```
pcall( f , arg1,···)
```

返回值

1. 函数执行状态 (boolean)
   - 没有错误返回 `true`
   - 有错误返回 `false`
2. 发生错误返回错误信息，否则返回函数调用返回值

pcall 示例

使用pcall 处理错误

```lua
function square(a)
  return a * "a"
end

local status, retval = pcall(square,10);

print ("Status: ", status)        -- 打印 "false" 
print ("Return Value: ", retval)  -- 打印 "input:2: attempt to perform arithmetic on a string value"
```

正常没错误

```lua
function square(a)
  return a * a
end

local status, retval = pcall(square,10);

print ("Status: ", status)        -- 打印 "true"
print ("Return Value: ", retval)  -- 打印 "100"
```

## xpcall

```
xpcall (f, msgh [, arg1, ···])
```

`xpcall` 类似 `pcall` xpcall接受两个参数：调用函数、错误处理函数

比如使用 debug.traceback 获取栈信息

```lua
> status, err, ret = xpcall(square, debug.traceback, 10)
> status
false
> err
stdin:2: attempt to perform arithmetic on a string value
stack traceback:
    stdin:2: in function 'square'
    [C]: in function 'xpcall'
    stdin:1: in main chunk
    [C]: in ?
>
```