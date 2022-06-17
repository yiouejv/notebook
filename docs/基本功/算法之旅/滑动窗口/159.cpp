/*
给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t ，并返回该子串的长度。

示例 1:

输入: "eceba"
输出: 3
解释: t 是 "ece"，长度为3。
示例 2:

输入: "ccaabbb"
输出: 5
解释: t 是 "aabbb"，长度为5。

*/


class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if (s.empty()) {
            return 0;
        }

        pair<char, int> first{s[0], 0};
        pair<char, int> second{0, 0};
        int size = s.size();
        int maxLen = 0;
        int i;

        for (i = 0; i < size; ++i) {
            if (s[i] != first.first) {
                if (second.first == 0) {
                    second = {s[i], i};

                } else if (s[i] != second.first) {
                    maxLen = max(maxLen, i - first.second);

                    second = {s[i], i};

                    first.first = s[i - 1];
                    int j = i;
                    while (s[--j] == s[i - 1]);
                    first.second = j + 1;
                }
            }
        }
        return max(maxLen, i - first.second);
    }
};
