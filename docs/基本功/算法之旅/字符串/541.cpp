/*
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 

示例 1：

输入：s = "abcdefg", k = 2
输出："bacdfeg"
示例 2：

输入：s = "abcd", k = 2
输出："bacd"
 

提示：

1 <= s.length <= 104
s 仅由小写英文组成
1 <= k <= 104

*/



class Solution {
public:
    string reverseStr(string s, int k) {
        int j = 0;
        bool flag = true;
        for (int i = 0; i < s.size(); ++i) {
            if (i - j + 1 == k) {
                if (flag) {
                    Reverse(s, j, i);
                    flag = false;
                } else {
                    flag = true;
                }
                j = i + 1;
            }
        }
        if (flag ) {
            Reverse(s, j, s.size() - 1);
        }
        return s;
    }
private:
    void Reverse(string &s, int i, int j) {
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
};


class Solution {
public:
    string reverseStr(string s, int k) {
        int size = s.size();
        // 1. 每隔2k 个字符的前k个字符进行反转
        // 2. 剩下的小于2k, 大于或等于k, 则反转前k个
        for (int i = 0; i < size; i += (2 * k)) {
            if (i + k <= size) {
                Reverse(s, i, i + k - 1);
                continue;
            }
            // 2. 剩下的小于k个，则全部反转
            Reverse(s, i, size - 1);
        }
        return s;
    }
private:
    void Reverse(string &s, int i, int j) {
        while (i < j) {
            swap(s[i++], s[j--]);
        }
    }
};
