--    写一个农民类Peasant有方法：
--        def farm(self, plant):
--            ...
--    写一个工人类Worker
--        方法如下：
--            def work(self, that):
--                ...
--    创建一个农民工为MigrantWorker, 让此类的对象拥有上面两个类的全部方法
--    person = MigrantWorker()
--    person.farm('水稻')  # 正在种植 水稻
--    person.work('汽车')  # 正在制造 汽车

-- Peasant 类
local Peasant = {}

function Peasant:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Peasant:farm(plant)
    print('正在种植'..plant)
end

-- Worker 类
Worker = {}

function Worker:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Worker:work(that)
    print('正在制造'..that)
end


-- MigrantWorker 类
MigrantWorker = {}

function MigrantWorker:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    self.farm = Peasant:new().farm
    self.work = Worker:new().work
    return o
end

-- 创建对象
local peasant = Peasant:new()
print(peasant:farm('水稻'))

local work = Worker:new()
print(work:work('汽车'))

local migrant_worker = MigrantWorker:new()
print(migrant_worker:farm('小麦'))
print(migrant_worker:work('汽车'))
