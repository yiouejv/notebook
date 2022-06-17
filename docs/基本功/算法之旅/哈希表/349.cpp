/*

给定两个数组，编写一个函数来计算它们的交集。

 
示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
示例 2：

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
 

说明：

输出结果中的每个元素一定是唯一的。
我们可以不考虑输出结果的顺序。

*/


class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map;
        for (int n : nums1) {
            map[n] = 1;
        }

        for (int n : nums2) {
            if (map.find(n) != map.end() && map[n] == 1) {
                map[n] = 0;
            }
        }

        vector<int> ans;
        for (auto [n, f] : map) {
            if (f == 0) {
                ans.push_back(n);
            }
        }
        return ans;
    }
};


class Solution {
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        unordered_set<int> result;

        for (int n : nums2) {
            if (nums_set.find(n) != nums_set.end()) {
                result.insert(n);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
