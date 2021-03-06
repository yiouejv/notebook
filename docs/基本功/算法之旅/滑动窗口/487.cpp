/*
给定一个二进制数组，你可以最多将 1 个 0 翻转为 1，找出其中最大连续 1 的个数。

示例 1：

输入：[1,0,1,1,0]
输出：4
解释：翻转第一个 0 可以得到最长的连续 1。
     当翻转以后，最大连续 1 的个数为 4。
 

注：

输入数组只包含 0 和 1.
输入数组的长度为正整数，且不超过 10,000
 

进阶：
如果输入的数字是作为 无限流 逐个输入如何处理？换句话说，内存不能存储下所有从流中输入的数字。您可以有效地解决吗？

*/


class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int size = nums.size();
        bool zero = false;
        int maxLen = 0;
        int i = 0;
        int j = 0;

        for (j = 0; i < size && j < size; ++j) {
            if (nums[j] == 0) {
                if (!zero) {
                    zero = true;
                } else {
                    maxLen = max(maxLen, j - i);
                    while (nums[i++] != 0);
                }
            }
        }
        return max(maxLen, j - i);
    }
};
