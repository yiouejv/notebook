/*
给你一个字符串 s ，逐个翻转字符串中的所有 单词 。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

请你返回一个翻转 s 中单词顺序并用单个空格相连的字符串。

说明：

输入字符串 s 可以在前面、后面或者单词间包含多余的空格。
翻转后单词间应当仅用一个空格分隔。
翻转后的字符串中不应包含额外的空格。
 

示例 1：

输入：s = "the sky is blue"
输出："blue is sky the"
示例 2：

输入：s = "  hello world  "
输出："world hello"
解释：输入字符串可以在前面或者后面包含多余的空格，但是翻转后的字符不能包括。
示例 3：

输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，将翻转后单词间的空格减少到只含一个。
示例 4：

输入：s = "  Bob    Loves  Alice   "
输出："Alice Loves Bob"
示例 5：

输入：s = "Alice does not even like bob"
输出："bob like even not does Alice"
 

提示：

1 <= s.length <= 104
s 包含英文大小写字母、数字和空格 ' '
s 中 至少存在一个 单词
 

进阶：

请尝试使用 O(1) 额外空间复杂度的原地解法。

*/

// 需要额外的空间
class Solution {
public:
    string reverseWords(string s) {
        string ans;
        int j = -1;  // 记录非空格的第一个字符，从后往前遍历，也就是单词的最后一个字符
        int i = 0;
        int size = s.size();
        for (i = size - 1; i >= 0; --i) {
            if (s[i] != ' ' && (i + 1 >= size || s[i + 1] == ' ')) {
                j = i;
            }
            if (s[i] == ' ' && j != -1) {
                for (int k = i + 1; k <= j; ++k) {
                    ans.push_back(s[k]);
                }
                ans.push_back(' ');
                j = -1;
            }
        }
        if (j != -1) {
            for (int k = i + 1; k <= j; ++k) {
                ans.push_back(s[k]);
            }
        } else {
            ans.erase(ans.end() - 1);
        }
        return ans;
    }
};

// O(1) 空间
class Solution {
public:
    string reverseWords(string s) {
        int size = s.size();
        // 反转整个字符串
        Reverse(s, 0, size - 1);

        // 去除多余的空格
        int i = 0;
        for (char c : s) {
            if (c != ' ') {
                s[i++] = c;
            } else if (i > 0 && s[i - 1] != ' ') {
                s[i++] = ' ';
            }
        }
        s = s[i - 1] != ' ' ? s.substr(0, i) : s.substr(0, i - 1);

        // 翻转单个单词
        i = 0;
        int newSize = s.size();
        for (int j = 0; j < newSize; ++j) {
            if (s[j] == ' ') {
                Reverse(s, i, j - 1);
                i = j + 1;
            }
        }
        // 翻转最后一个单词
        Reverse(s, i, newSize - 1);
        return s;
    }
private:
    void Reverse(string &s, int start, int end) {
        while (start < end) {
            swap(s[start++], s[end--]);
        }
    }
};
