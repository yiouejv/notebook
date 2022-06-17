/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

 

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
示例 2：

输入：nums = []
输出：[]
示例 3：

输入：nums = [0]
输出：[]
 

提示：

0 <= nums.length <= 3000
-105 <= nums[i] <= 105

*/


// hashtable
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) {
            return {};
        }
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        unordered_set<int> set;

        int size = nums.size();
        // a + b + c = 0
        for (int i = 0; i < size; ++i) {
            if (nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {  // a 去重
                continue;
            }
            for (int j = i + 1; j < size; ++j) {
                //-4 -1 -1 -1 0 1 2
                //-4 -2 2 2 0 1 2
                if (j > i + 2
                        && nums[j] == nums[j - 1]
                        && nums[j] == nums[j - 2]) {
                    continue;
                } // b 去重
                int a = nums[i], b = nums[j];
                int c = -(a + b);
                if (set.find(c) != set.end()) {
                    ans.push_back( {a, b, c} );
                    set.erase(c);  // c 去重
                } else {
                    set.insert(b);
                }
            }
            set.clear();
        }
        return ans;
    }
};

// double pointer
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) {
            return {};
        }
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int i = 0, j = 0;

        vector<vector<int>> ans;
        while (i < size - 2) {
            if (nums[i] > 0) {
                break;
            }
            j = size - 1;
            while (j - i > 1) {
                int n = nums[i] + nums[j];
                int target = 0 - n;
                int index = BinarySearch(nums, i + 1, j - 1, target);  // find b
                if (index != -1) {
                    ans.push_back({nums[i], nums[index], nums[j]});
                }
                while (j - i > 1 && nums[--j] == nums[j + 1]);  // c 去重
            }
            while (i < size - 2 && nums[++i] == nums[i - 1]);  // a 去重
        }
        return ans;
    }
private:
    int BinarySearch(const vector<int> &nums, int start, int end, int target) {
        int i = start, j = end;
        while (i <= j) {
            int m = i + (j - i) / 2;
            if (nums[m] == target) {
                return m;
            } else if (nums[m] < target) {
                i = m + 1;
            } else {
                j = m - 1;
            }
        }
        return -1;
    }
};

