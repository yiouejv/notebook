/*
给出三个均为 严格递增排列 的整数数组 arr1，arr2 和 arr3。

返回一个由 仅 在这三个数组中 同时出现 的整数所构成的有序数组。

 

示例：

输入: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
输出: [1,5]
解释: 只有 1 和 5 同时在这三个数组中出现.
 

提示：

1 <= arr1.length, arr2.length, arr3.length <= 1000
1 <= arr1[i], arr2[i], arr3[i] <= 2000

*/
class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        vector<int> ans;
        int n = arr1.size();
        for (int i = 0; i < n; ++i) {
            if (BinarySearch(arr2, arr1[i]) && BinarySearch(arr3, arr1[i])) {
                ans.push_back(arr1[i]);
            }
        }
        return ans;
    }

private:
    bool BinarySearch(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == target) {
                return true;
            } else if (nums[m] < target) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return false;
    }
};
