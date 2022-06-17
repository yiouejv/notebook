/*
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

 

示例 1：

输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
示例 2：

输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
 

提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 已按 非递减顺序 排序
 

进阶：

请你设计时间复杂度为 O(n) 的算法解决本问题

*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int size = nums.size();

        for (int k = 0; k < size; ++k) {
            nums[k] = nums[k] * nums[k];
        }
        sort(nums.begin(), nums.end());
        return nums;
    }
};



/* 如果在原数组上操作
 * -7 -3 0 3 11   i = 0, j = 4
 * -7 -3 0 3 121  i = 0, j = 3
 * -7 -3 0 49 121 i = 1, j = 3
 * -7 -3 0 2401 121 i = 1, j = 3
 * -7 -3 0 5764801 121 i = 1, j = 3
 * -7 -3 0 5764801*5764801 121 i = 1, j = 3
 *  ...  死循环了
 */

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int size = nums.size();
        int pos = size - 1;
        vector<int> ans(size, 0);

        for (int i = 0, j = size - 1; i <= j;) {
            int i2 = nums[i] * nums[i];
            int j2 = nums[j] * nums[j];
            if (i2 < j2) {
                ans[pos--] = j2;
                --j;
            } else {
                ans[pos--] = i2;
                ++i;
            }
        }
        return ans;
    }
};


