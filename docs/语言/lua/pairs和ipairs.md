### 例子一

```lua
local arr = {1, 2, 3, nil, 4, 5, 6, 7, k='123', r = nil, 8, 9}

for k, v in pairs(arr) do
	print("k:", k, "v:", v)
end
print('------------------------')

for k, v in ipairs(arr) do
	print("k:", k, "v:", v)
end
print('------------------------')

--[[
k:	1	v:	1
k:	2	v:	2
k:	3	v:	3
k:	5	v:	4
k:	6	v:	5
k:	7	v:	6
k:	8	v:	7
k:	9	v:	8
k:	10	v:	9
k:	k	v:	123
------------------------
k:	1	v:	1
k:	2	v:	2
k:	3	v:	3
------------------------
]]

-- 结论：pairs 会遍历出所有类型的元素，但会删除数组和hash的nil
```

### 例子二

```lua
local arr = {1, 2, 3, 4, 5, 6, 7, k='123', r=nil, 8, 9}

for k, v in pairs(arr) do
	print("k:", k, "v:", v)
end
print('------------------------')

for k, v in ipairs(arr) do
	print("k:", k, "v:", v)
end
print('------------------------')

--[[
k:	1	v:	1
k:	2	v:	2
k:	3	v:	3
k:	4	v:	4
k:	5	v:	5
k:	6	v:	6
k:	7	v:	7
k:	8	v:	8
k:	9	v:	9
k:	k	v:	123
------------------------
k:	1	v:	1
k:	2	v:	2
k:	3	v:	3
k:	4	v:	4
k:	5	v:	5
k:	6	v:	6
k:	7	v:	7
k:	8	v:	8
k:	9	v:	9
------------------------
]]

-- 结论：ipairs 会过滤掉hash类型，但遇到数组nil会停止
```

