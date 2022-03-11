
-- local util = loadfile("./util.lua")()
require("util")

local function TestConcatList()
    local dest = {}
    local src = {}
    table.ConcatList(dest, src)
    PRINT("dest:", dest)

    dest = {}
    src = {1, 2, 3}
    table.ConcatList(dest, src)
    PRINT("dest:", dest)

    dest = {1, 2}
    src = {1, 2, 3}
    table.ConcatList(dest, src)
    PRINT("dest:", dest)
end

function TestUpdate()
    local dest = {0, 0, 0, 0}
    local src = {1, 2, 3}
    table.Update(dest, src)
    PRINT("ssssssssssssssss", dest)
end

function main()
    TestConcatList()
    -- TestUpdate()
end

main()
