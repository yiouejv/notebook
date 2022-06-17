/*
给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

如果可以，返回 true ；否则返回 false 。

magazine 中的每个字符只能在 ransomNote 中使用一次。

 

示例 1：

输入：ransomNote = "a", magazine = "b"
输出：false
示例 2：

输入：ransomNote = "aa", magazine = "ab"
输出：false
示例 3：

输入：ransomNote = "aa", magazine = "aab"
输出：true
 

提示：

1 <= ransomNote.length, magazine.length <= 105
ransomNote 和 magazine 由小写英文字母组成

*/



class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> map;
        for (char c : magazine) {
            ++map[c];
        }

        for (char c : ransomNote) {
            if (--map[c] < 0) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> vec(26, 0);
        for (char c : magazine) {
            ++vec[c - 'a'];
        }

        for (char c : ransomNote) {
            if (--vec[c - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};
