function Uuid()
    local seed={
        '1','2','3','4','5','6','7','8','9','0',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
    }
    local tb = {}
    for i = 1, 32 do
        table.insert(tb, seed[math.random(1, 36)])
    end
    local sid=table.concat(tb)
    return string.format('%s%s%s%s%s',
        string.sub(sid,1,8),
        string.sub(sid,9,12),
        string.sub(sid,13,16),
        string.sub(sid,17,20),
        string.sub(sid,21,32)
    )
end

--------------------------------------- table
--[[ 合并两个 list ]]
function table.ConcatList(dest, src)
    for i, v in ipairs(src) do
        dest[#dest + 1] = v
    end
end

--[[ 更新 dest 的字典值 ]]
function table.Update(dest, src)
    for k, v in pairs(src) do
        dest[k] = v
    end
end

function table.ValueAdd(dest, src)
    for k, v in pairs(src) do
        dest[k] = (dest[k] or 0) + v
    end
end

function table.Copy(t)
    local r = {}
    for k, v in pairs(t) do
        r[k] = v
    end
    return r
end

function table.DeepCopy(src, quiet)
    if type(src) ~= "table" then
        return src
    end
    local cache = {}
    local function CloneTable(t, level)
        if not level then
            level = 0
        end

        if level > 20 then
            if not quiet then
                error("table clone failed, source table is too deep!")
            else
                return t
            end
        end

        local rel = {}
        for k, v in pairs(t) do
            if type(v) == "table" then
                if cache[v] then
                    rel[k] = cache[v]
                else
                    rel[k] = CloneTable(v, level + 1)
                    cache[v] = rel[k]
                end
            else
                rel[k] = v
            end
        end
        local mt = getmetatable(t)
        if mt then
            setmetatable(rel, mt)
        end
        return rel
    end
    return CloneTable(src)
end
--------------------------------------- end table

--------------------------------- PRINT

local _esc_table = {
    ["\n"] = "\\n",
    ["\r"] = "\\r",
    ["\t"] = "\\t",
    ["\b"] = "\\b",
    ["\v"] = "\\v",
    ["\\"] = "\\\\",
    ["\""] = "\\\"",
}

local function _STR_STRING(str)
    str = string.gsub(str, ".", function(c)
        return _esc_table[c] or c
    end)
    str = string.gsub(str, "[^%w%p ]", function(c)
        return string.format("\\x%02x", string.byte(c))
    end)
    return '"' .. str .. '"'
end

function _STR_TABLE(obj, indent, checker)
    indent = indent or ""
    if string.len(indent) > 20 then
        return indent .. "..."
    end
    checker = checker or {}
    checker[obj] = true
    local ret = {}
    ret[1+#ret] = indent .. tostring(obj) .. " {\n"
    for k,v in pairs(obj) do
        if type(k) == "table" then
            ret[1+#ret] = indent .. "  " .. tostring(k) .. ": =====>" .. tostring(v) .. "\n"
        elseif type(v) == "table" then
            if checker[v] then
                -- 递归了
                ret[1+#ret] = indent .. "  " .. STR(k) .. ": =====>" .. tostring(v) .. "\n"
            else
                ret[1+#ret] = indent .. "  " .. STR(k) .. ":\n"
                ret[1+#ret] = _STR_TABLE(v, indent .. "  ", checker) .. "\n"
            end
        else
            ret[1+#ret] = indent .. "  " .. STR(k) .. ": " .. STR(v) .. "\n"
        end
    end
    ret[1+#ret] = indent .. "}"
    checker[obj] = nil
    return table.concat(ret, "")
end

-- 转换为字符串
function STR(obj)
    if type(obj) == "table" then
        return _STR_TABLE(obj)
    elseif type(obj) == "string" then
        return _STR_STRING(obj)
    elseif obj == nil then
        return "nil"
    else
        return tostring(obj)
    end
end

-- 调试用的print
function PRINT(...)
    local args = {...}
    local max_index = 0
    for k,v in pairs(args) do
        max_index = k>max_index and k or max_index
    end
    for i=1,max_index do
        args[i] = STR(args[i])
    end
    local str = table.concat(args, ", ")
    local pre = string.char(0x1b) .. "[1;33;40m"
    local suf = string.char(0x1b) .. "[0m"
    print(pre .. str .. suf)
end

------------------------------------------- end PRINT