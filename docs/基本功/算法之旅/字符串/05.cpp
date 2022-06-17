/*
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

 

示例 1：

输入：s = "We are happy."
输出："We%20are%20happy."
 

限制：

0 <= s 的长度 <= 10000

*/


class Solution {
public:
    string replaceSpace(string s) {
        string ans;
        for (char c : s) {
            if (c == ' ') {
                ans.push_back('%');
                ans.push_back('2');
                ans.push_back('0');
            } else {
                ans.push_back(c);
            }
        }
        return ans;
    }
};


class Solution {
public:
    string replaceSpace(string s) {
        int count = 0;
        for (char c : s) {
            if (c == ' ') {
                ++count;
            }
        }
        if (count == 0) {
            return s;
        }

        int i = s.size() - 1;  // 扩展容量前的尾元素的下标
        s.resize(s.size() + count * 2);
        int j = s.size() - 1;  // 扩展容量后的尾元素的下标
        while (i >= 0) {
            if (s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            } else {
                s[j--] = s[i];
            }
            --i;
        }
        return s;
    }
};
