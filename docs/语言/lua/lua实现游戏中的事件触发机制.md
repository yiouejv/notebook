
今天总结一下游戏架构中的事件触发机制，游戏架构中为什么需要由事件驱动。

主要是为了解耦，所谓高内聚，低耦合，如果不采用事件驱动的方式，则会像下面这样来写代码。

比如说，游戏内有多个玩法模块，”玩家“在打造装备的时候，可能触发”装备打造xx阶的成就“，也可能达成某种条件获得了时装。

这种情景的话，如果没有采用事件驱动的方式来写代码，则需要在装备模块的”升级装备“函数内调用 成就模块 的检查成就达成的函数，还需要调用 时装模块 的检查获得时装的函数。

```lua
function equipStrengthen()
	-- 装备强化逻辑

	checkAchievement()  -- 成就模块检查成就
	checkObtainFashion()  -- 时装模块检查获得时装
end
```

如果装备关联的模块越来越多的话，就要记得去相关的函数内添加相关的调用。

事件驱动的方式就比较好的处理了这种情况。 如果是用事件驱动的方式来处理以上问题，则我们会这么做，由装备模块发出“装备强化”的事件，成就模块和时装模块只需要监听”装备强化“事件做相应的处理就好了。

在装备强化的模块内只需要一行代码，发出事件，后续如果需要增加关联的模块时，装备模块完全不用动，新模块只要增加监听事件就可以了。

下面我用lua实现一个例子:

```lua
------------------------------------------------------ 事件触发器
local Listener = {}
function Listener:new(channel, callback)
    local obj = {
        callback = callback,
        channel = channel,
    }
    setmetatable(obj, self)
    self.__index = self
    return obj
end


local Channel = {}
function Channel:new(event)
    assert(event)
    local obj = {
        listeners = {},
        event = event,
    }
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function Channel:on(callback)
    listener = Listener:new(self, callback)
    table.insert(self.listeners, listener)
end


local EventEmitter = {}
function EventEmitter:new()
    local obj = {
        events = {},  -- 监听的所有事件
        channels = {}, -- event: channel
    }
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function EventEmitter:setEvents(events)
    self.events = events
end

function EventEmitter:on(event, callback)
    assert(event)
    assert(callback)
    if not self.events[event] then
        error("not register event: "..event)
    end
    local channel = self.channels[event]
    if not channel then
        channel = Channel:new(event)
        self.channels[event] = channel
    end
    channel:on(callback)
end

function EventEmitter:emit(event)
    if not self.events[event] then
        error("not register event: "..event)
    end

    local channel = self.channels[event]
    if not channel then return end

    for _, listener in ipairs(channel.listeners) do
        listener.callback()
    end
end
----------------------------------------------------- 装备模块
local eventEmitter = EventEmitter:new()
eventEmitter:setEvents({
    ["equipStrengthen"] = "装备强化",
})


function equipStrengthen()
    -- 装备强化逻辑
    eventEmitter:emit("equipStrengthen")
end

------------------------------------------------------ 成就模块
function checkAchievement()
    print('checkAchievement')
end

eventEmitter:on("equipStrengthen", checkAchievement)  -- 成就模块注册监听

------------------------------------------------------ 时装模块
function checkObtainFashion()
    print('checkObtainFashion')
end

eventEmitter:on("equipStrengthen", checkObtainFashion)  -- 时装模块注册监听
------------------------------------------------------------------------------------
function main()
    equipStrengthen()
end

main()
```

最后输出:

```lua
checkAchievement
checkObtainFashion
```

下面这个图可以有助于理解，

<img src="../evevnEmitter.png">


上述的实现比较简单，主要意思表达出来了，具体的细节可以结合需要再添加就好了。
