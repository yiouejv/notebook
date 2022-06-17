/*
给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。

返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。

 

示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
示例 2:

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]
 

提示：

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
 

进阶：

如果给定的数组已经排好序呢？你将如何优化你的算法？
如果 nums1 的大小比 nums2 小，哪种方法更优？
如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？

*/
// 未排序的版本，利用两个unordered_map求解。
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map1;
        unordered_map<int, int> map2;

        for (int n : nums1) {
            map1[n]++;
        }

        for (int n : nums2) {
            map2[n]++;
        }

        vector<int> ans;
        for (auto it = map1.begin(); it != map1.end(); ++it) {
            int count = min(it->second, map2[it->first]);
            for (int i = 0; i < count; ++i) {
                ans.push_back(it->first);
            }
        }
        return ans;
    }
};

// 利用一个unordered_map, 保存较短的数组里的数出现的次数
// 遍历较长的数组，判断整数map, 存在map的值-1，并把该整数写入答案。
// 较短的数组记录map值比较长的数组更节省空间
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }

        unordered_map<int, int> map;
        for (int n : nums1) {
            map[n]++;
        }

        vector<int> ans;
        for (int n : nums2) {
            if (map[n] > 0) {
                ans.push_back(n);
            }
            map[n] --;
        }
        return ans;
    }
};

// 数组有序的话使用双指针
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        vector<int> ans;
        int i = 0,
            j = 0;

        while (i < size1 && j < size2) {
            if (nums1[i] > nums2[j]) {
                ++j;
            } else if (nums1[i] < nums2[j]) {
                ++i;
            } else {
                ans.push_back(nums1[i]);
                ++i;
                ++j;
            }
        }
        return ans;
    }
};
