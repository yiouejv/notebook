/*
给定一个字符串 s ，找出 至多 包含 k 个不同字符的最长子串 T。

 

示例 1:

输入: s = "eceba", k = 2
输出: 3
解释: 则 T 为 "ece"，所以长度为 3。
示例 2:

输入: s = "aa", k = 1
输出: 2
解释: 则 T 为 "aa"，所以长度为 2。
 

提示：

1 <= s.length <= 5 * 104
0 <= k <= 50

*/


class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) {
            return 0;
        }
        unordered_map<char, int> map;
        int i = 0;
        int j = 0;
        int size = s.size();
        int maxLen = 0;

        while (i < size && j < size) {
            map[s[j++]]++;
            if (map.size() > k) {
                map[s[i]]--;
                if (map[s[i]] <= 0) {
                    map.erase(s[i]);
                }
                ++i;
            } else {
                maxLen = max(maxLen, j - i);
            }
        }
        return maxLen;
    }
};
