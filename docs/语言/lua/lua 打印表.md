### lua 打印表

~~~ lua
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

local _esc_table = {
    ["\n"] = "\\n",
    ["\r"] = "\\r",
    ["\t"] = "\\t",
    ["\b"] = "\\b",
    ["\v"] = "\\v",
    ["\\"] = "\\\\",
    ["\""] = "\\\"",
}
function _STR_STRING(str)
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
    print(table.concat(args, ", "))
end

~~~