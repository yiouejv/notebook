实现一个lua单链表，备用。

### 代码如下

```lua
--[[
	数据结构: 单链表
]]


local Node = {}
local LinkList = {}

function Node:new(value)
	local o = {value=value, next=nil}
	setmetatable(o, self)
	self.__index = self
	return o
end

function LinkList:__new__(seq)
	node = Node:new()
	local obj = {head=node, tail=node, len=0}

	setmetatable(obj, self)
	self.__index = self
	if seq then LinkList.__init__(obj, seq) end
	return obj
end

function LinkList:__init__(seq)
	if type(seq) ~= 'table' then error(seq..' not is itertor object') end

	local cur_node = self.head
	for k, v in pairs(seq) do
		node = {value=v, next=nil}
		cur_node.next = node
		cur_node = node
		self.tail = cur_node
		self.len = self.len + 1
	end
end

function LinkList:iter()
	local cur_node = self.head
	return function()
		cur_node = cur_node.next
		if cur_node then
			return cur_node, cur_node.value
		end
	end
end

function LinkList:iter_print()
	for k,v in self:iter() do
		print('value: '.. v .. ' next: ', k)
	end
end

function LinkList:append(value)
	local node = Node:new(value)

	self.tail.next = node
	self.tail = node
	self.len = self.len + 1
end

function LinkList:remove(value)
	if self.len == 0 then error('from empty linklist remove') end
	local pre_node = self.head
	local cur_node = pre_node.next

	while cur_node.value ~= value do
		pre_node = cur_node
		cur_node = cur_node.next
	end

	pre_node.next = cur_node.next

	-- 如果删除的节点为尾节点
	if cur_node == self.tail then
		self.tail = pre_node
	end

	-- 如果删除的节点为头节点
	if cur_node == self.head then
		self.head = cur_node.next
	end

	cur_node = nil
	self.len = self.len - 1
end

function LinkList:pop()
	if self.len == 0 then error('from empty linklist pop') end

	local pre_node = self.head
	local cur_node = pre_node.next

	while cur_node ~= self.tail do
		pre_node = pre_node.next
		cur_node = cur_node.next
	end

	local value = self.tail.value
	self.tail = pre_node
	self.tail.next = nil
	self.len = self.len - 1
	return value
end

function LinkList:append_left(value)
	local node = Node:new(value)
	node.next = self.head.next
	self.head.next = node
	self.len = self.len + 1
end


function linklist_test()
	-- 单测
	--- 创建空链表
	local ll = LinkList:__new__()
	assert(ll.len == 0)
	ll:iter_print()

	-- 尾部追加元素
	ll:append(1)
	assert(ll.len == 1)
	ll:iter_print()

	ll:append(2)
	ll:append(3)
	ll:remove(2)
	assert(ll.len == 2)
	ll:iter_print()

	print('##############################')
	--- 非空链表测试
	local t = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
	local ll = LinkList:__new__(t)
	ll:iter_print()
	assert(ll.len == 10)

	ll:append(11)
	assert(ll.len == 11)
	ll:iter_print()
	
	assert(ll:pop() == 11)
	assert(ll.len == 10)
	ll:iter_print()

	assert(ll:pop() == 0)
	assert(ll.len == 9)
	ll:iter_print()

	ll:append_left(0)
	assert(ll.len == 10)
	ll:iter_print()

	ll:append_left(-1)
	assert(ll.len == 11)
	ll:iter_print()
end


-- linklist_test()


return LinkList
```

