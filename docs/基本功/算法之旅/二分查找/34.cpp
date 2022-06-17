/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？
 

示例 1：

输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
示例 2：

输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
示例 3：

输入：nums = [], target = 0
输出：[-1,-1]
 

提示：

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums 是一个非递减数组
-109 <= target <= 109
*/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0;
        int n = nums.size();
        int r = n - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) {

                // 寻找左边界
                int left = m;
                while (left - 1 >= 0 && nums[left - 1] == target) --left;

                // 寻找右边界
                int right = m;
                while (right + 1 < n && nums[right + 1] == target) ++right;
                return {left, right};

            } else if (nums[m] > target) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return {-1, -1};
    }
};

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0;
        int n = nums.size();
        int r = n;

        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) {

                // 寻找左边界
                int left = m;
                while (left - 1 >= 0 && nums[left - 1] == target) --left;

                // 寻找右边界
                int right = m;
                while (right + 1 < n && nums[right + 1] == target) ++right;
                return {left, right};

            } else if (nums[m] > target) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return {-1, -1};
    }
};


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBorder = -2;
        int rightBorder = -2;
        leftBorder = GetLeftBorder(nums, target);
        rightBorder = GetRightBorder(nums, target);
        // target 在数组的左边或右边
        if (leftBorder == -2 || rightBorder == -2) {
            return {-1, -1};
        }
        // 找到了元素
        if (rightBorder - leftBorder > 1) {
            return {leftBorder + 1, rightBorder - 1};
        }
        // target 在数组范围内，并且不存在
        return {-1, -1};
    }
private:
    int GetLeftBorder(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        int leftBorder = -2;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] >= target) {
                r = m - 1;
                leftBorder = r;
            } else {
                l = m + 1;
            }
        }
        return leftBorder;
    }

    int GetRightBorder(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        int rightBorder = -2;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] > target) {
                r = m - 1;
            } else {
                l = m + 1;
                rightBorder = l;
            }
        }
        return rightBorder;
    }
};


