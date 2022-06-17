/*
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

 

示例 1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：

输入：target = 4, nums = [1,4,4]
输出：1
示例 3：

输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
 

提示：

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105
 

进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。

*/
/* 本题的窗口是什么？  满足条件 sum >= target 的连续子数组。
 * 什么时候移动开始位置？ 当满足条件时，减少子数组的元素，尝试获得最短子数组
 * 什么时候移动结束位置？当不满足条件时，增加子数组的长度，使得数组的和尽量能够满足条件。
 */

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int size = nums.size();
        int i = 0,
            j = 0;
        int sum = nums[0];
        int minLen = INT32_MAX;

        while (i < size && j < size) {
            if (sum >= target) {
                minLen = min(minLen, j - i + 1);
            }
            if (sum < target) {
                if (++j < size) {
                    sum += nums[j];
                }
            } else {
                sum -= nums[i++];
            }
        }
        return minLen == INT32_MAX ? 0 : minLen;
    }
};
