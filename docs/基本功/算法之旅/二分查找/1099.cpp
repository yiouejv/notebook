/*
给你一个整数数组 nums 和整数 k ，返回最大和 sum ，满足存在 i < j 使得 nums[i] + nums[j] = sum 且 sum < k 。如果没有满足此等式的 i,j 存在，则返回 -1 。

示例 1：

输入：nums = [34,23,1,24,75,33,54,8], k = 60
输出：58
解释：
34 和 24 相加得到 58，58 小于 60，满足题意。
示例 2：

输入：nums = [10,20,30], k = 15
输出：-1
解释：
我们无法找到和小于 15 的两个元素。
 

提示：

1 <= nums.length <= 100
1 <= nums[i] <= 1000
1 <= k <= 2000

*/
class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int maxValue = -1;
        for (int i = 0; i < n; ++i) {
            int ans = GetSumLessThanK(nums, i, k);
            if (ans != -1) {
                if (maxValue == -1) {
                    maxValue = ans;
                } else {
                    maxValue = max(maxValue, ans);
                }
            }
        }
        return maxValue;
    }

private:
    int GetSumLessThanK(vector<int>& nums, int i, int k) {
        int maxValue = -1;
        int n = nums.size();
        int l = i + 1;
        int r = n - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            int sum = nums[i] + nums[m];
            if (sum < k) {
                if (maxValue == -1) {
                    maxValue = sum;
                } else {
                    maxValue = max(sum, maxValue);
                }
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return maxValue;
    }
};
