/*
给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，请你判断二者是否相等。# 代表退格字符。

如果相等，返回 true ；否则，返回 false 。

注意：如果对空文本输入退格字符，文本继续为空。

 

示例 1：

输入：s = "ab#c", t = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。
示例 2：

输入：s = "ab##", t = "c#d#"
输出：true
解释：s 和 t 都会变成 “”。
示例 3：

输入：s = "a##c", t = "#a#c"
输出：true
解释：s 和 t 都会变成 “c”。
示例 4：

输入：s = "a#c", t = "b"
输出：false
解释：s 会变成 “c”，但 t 仍然是 “b”。
 

提示：

1 <= s.length, t.length <= 200
s 和 t 只含有小写字母以及字符 '#'
 

进阶：

你可以用 O(N) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？

*/

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        string s1 = GetLastString(s);
        string t1 = GetLastString(t);
        return s1 == t1;
    }

private:
    string GetLastString(const string& s) {
        int j = 0;
        int size = s.size();
        string str;

        for (int i = 0; i < size; ++i) {
            if (s[i] == '#') {
                if (!str.empty()) {
                    str.pop_back();
                }
            } else {
                str.push_back(s[i]);
            }
        }
        return str;
    }
};


class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int sSize = s.size();
        int tSize = t.size();
        int i = sSize - 1;
        int j = tSize - 1;
        int sCount = 0;
        int tCount = 0;

        while (i >= 0 || j >= 0) {
            while (i >= 0 && (s[i] == '#' || sCount != 0)) {
                if (s[i] == '#') {
                    ++ sCount;
                } else {
                    -- sCount;
                }
                --i;
            }

            while (j >= 0 && (t[j] == '#' || tCount != 0)) {
                if (t[j] == '#') {
                    ++ tCount;
                } else {
                    -- tCount;
                }
                --j;
            }

            if (i < 0 && j < 0) {
                return true;
            } else if (i >= 0 && j >= 0) {
                if (s[i] != t[j]) {
                    return false;
                } else {
                    --i;
                    --j;
                }
            } else {
                return false;
            }
        }
        return true;
    }
};

