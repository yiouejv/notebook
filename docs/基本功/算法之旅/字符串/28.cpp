/*
实现 strStr() 函数。

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

 

说明：

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java 的 indexOf() 定义相符。

 

示例 1：

输入：haystack = "hello", needle = "ll"
输出：2
示例 2：

输入：haystack = "aaaaa", needle = "bba"
输出：-1
示例 3：

输入：haystack = "", needle = ""
输出：0
 

提示：

0 <= haystack.length, needle.length <= 5 * 104
haystack 和 needle 仅由小写英文字符组成

*/

// 双指针
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle == "") {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }
        int i = -1, j = 0;
        int index = 0;
        while (index < haystack.size()) {
            if (haystack[index++] == needle[j]) {
                if (i == -1) {
                    i = index - 1;
                }
                if (++j >= needle.size()) {
                    break;
                }
            } else if (i != -1) {
                index = i + 1;
                i = -1, j = 0;
            }
        }
        return j >= needle.size() ? i : -1;
    }
};


// 滑动窗口
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle == "") {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }
        int i;
        for (i = 0; i + needle.size() <= haystack.size(); ++i) {
            if (IsEqual(haystack, i, i + needle.size(), needle)) {
                return i;
            }
        }
        return -1;
    }
private:
    bool IsEqual(const string &haystack, int start, int end, const string &needle) {
        int j = 0;
        for (int i = start; i < end; ++i) {
            if (haystack[i] != needle[j++]) {
                return false;
            }
        }
        return true;
    }
};

// 前缀: 以第一个字符开头，不包含最后一个字符的连续子串
// 后缀: 以最后一个字符开头，不包含第一个字符的连续子串
//
// kmp 算法
// aabaa
// 前缀 a aa aab aaba
// 后缀 a aa baa abaa
// 2
//
// aaba
// 前缀 a aa aab
// 后缀 a ba aba
// 1
//
// aab
// 前缀 a aa
// 后缀 b ab
// 0
//
// aa
// 前缀 a
// 后缀 a
// 1
//
// a
// 0


class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        vector<int> prefix(needle.size(), 0);
        GetPrefix(prefix, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); ++i) {
            while (j > 0 && needle[j] != haystack[i]) {
                j = prefix[j - 1];
            }
            if (needle[j] == haystack[i]) {
                j ++;
            }
            if (j >= needle.size()) {
                return i - needle.size() + 1;
            }
        }
        return -1;
    }
    void GetPrefix(vector<int>& prefix, const string& needle) {
        int j = 0;
        for (int i = 1; i < needle.size(); ++i) {
            while (j > 0 && needle[j] != needle[i]) {
                j = prefix[j - 1];
            }
            if (needle[j] == needle[i]) {
                ++j;
            }
            prefix[i] = j;
        }
    }
};
