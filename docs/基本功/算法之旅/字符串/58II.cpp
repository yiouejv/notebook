/*
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。

请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

示例 1：

输入: s = "abcdefg", k = 2
输出: "cdefgab"
示例 2：

输入: s = "lrloseumgh", k = 6
输出: "umghlrlose"
 

限制：

1 <= k < s.length <= 10000

*/


// 使用额外空间n, 最坏情况为s的长度
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int size = s.size();
        s.resize(size + n);
        int newSize = s.size();

        // 把前n个字符挪到最后面
        for (int i = 0; i < n; ++i) {
            s[size + i] = s[i];
        }
        // [n, newSize) 整体往前挪
        for (int i = 0; i < size; ++i) {
            s[i] = s[n + i];
        }
        s.resize(size);
        return s;
    }
};

// 不适用额外的空间, O(1)
// abcdefg
// ba gfedc
// cdefgab
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};
