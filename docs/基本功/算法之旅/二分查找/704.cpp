/* 输入: nums = [-1,0,3,5,9,12], target = 9 */
/* 输出: 4 */
/* 解释: 9 出现在 nums 中并且下标为 4 */

/* 输入: nums = [-1,0,3,5,9,12], target = 2 */
/* 输出: -1 */
/* 解释: 2 不存在 nums 中因此返回 -1 */

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) {
                return m;
            } else if (nums[m] < target) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return -1;
    }
};

class Solution {
public:
   int search(vector<int> &nums, int target) {
        int l = 0;
        int r = nums.size();
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] > target) {
                r = m;
            } else if (nums[m] < target) {
                l = m + 1;
            } else {
                return m;
            }
        }
        return -1;
   }
};
