/*
给你一个字符串 S，找出所有长度为 K 且不含重复字符的子串，请你返回全部满足要求的子串的数目。

 

示例 1：

输入：S = "havefunonleetcode", K = 5
输出：6
解释：
这里有 6 个满足题意的子串，分别是：'havef','avefu','vefun','efuno','etcod','tcode'。
示例 2：

输入：S = "home", K = 5
输出：0
解释：
注意：K 可能会大于 S 的长度。在这种情况下，就无法找到任何长度为 K 的子串。
 

提示：

1 <= S.length <= 10^4
S 中的所有字符均为小写英文字母
1 <= K <= 10^4

*/



class Solution {
public:
    int numKLenSubstrNoRepeats(const string& s, int k) {
        int size = s.size();
        if (k > size) {
            return 0;
        }

        unordered_map<char, int> map;
        int i = 0;
        int j = 0;
        int ans = 0;

        for (; j < size; ++j) {
            if (map.find(s[j]) != map.end()) {
                int k = i;
                while (s[k++] != s[j]);
                j = k;
                i = k;  // 记得更新i

                map.clear();
            }
            map[s[j]]++;
            if (map.size() == k) {
                ++ans;
                map.erase(s[i++]);
            }
        }
        return ans;
    }
};


// 固定长度的滑动窗口
class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        int size = s.size();
        if (k > size) {
            return 0;
        }
        int ans;
        for (int i = 0; i < size - k + 1; ++i) {
            if (NoRepeats(s.substr(i, k))) {
                ans++;
            }
        }
        return ans;
    }

private:
    bool NoRepeats(const string& s) {
        unordered_map<char, int> map;
        for (char c : s) {
            if (map.find(c) != map.end()) {
                return false;
            }
            map[c]++;
        }
        return true;
    }
};

// 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
// 内存消耗： 6.3 MB , 在所有 C++ 提交中击败了99.32%的用户
class Solution {
public:
    int numKLenSubstrNoRepeats(const string& s, int k) {
        int size = s.size();
        if (k > size) {
            return 0;
        }

        vector<int> arr(26, 0);
        int count = 0;
        int i = 0;
        int j = 0;
        int ans = 0;

        for (; j < size; ++j) {
            if (arr[ GetIndex(s[j]) ]) {
                // j 从当前字符下一个字符开始继续找
                int k = i;
                while (s[k++] != s[j]);
                j = k; i = k;  // 记得更新i
                count = 0;

                arr.assign(26, 0);
            }

            arr[ GetIndex(s[j]) ] = 1;
            ++count;

            if (count == k) {
                ++ans; --count;
                arr[ GetIndex(s[i++]) ] = 0;
            }
        }
        return ans;
    }
private:
    int GetIndex(char c) {
        return c - 'a';
    }
};
