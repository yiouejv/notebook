/*
给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。

请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

 

示例 1：

输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：

输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
 

提示：

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

*/


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int size = nums.size();
        if (size < 4) {
            return {};
        }
        sort(nums.begin(), nums.end());
        int i = 0, j, k, l;
        vector<vector<int>> ans;

        while (i < size - 3) {
            j = size - 1;
            while (j - i > 2) {
                k = i + 1;
                while (k < j - 1) {
                    long long tar = target - ((long long)nums[i] + nums[k] + nums[j]);
                    int index = BinarySearch(nums, tar, k + 1, j - 1);
                    if (index != -1) {
                        ans.push_back({ nums[i], nums[k], nums[index], nums[j]});
                    }
                    while (k < j - 1 && nums[++k] == nums[k - 1]);
                }
                while (j - i > 2 && nums[--j] == nums[j + 1]);
            }
            while (i < size - 3 && nums[++i] == nums[i - 1]);
        }
        return ans;
    }
private:
    int BinarySearch(const vector<int> &nums, long long target, int start, int end) {
        int l = start, r = end;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) {
                return m;
            } else if (nums[m] > target) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return -1;
    }
};
