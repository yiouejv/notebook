/*
魔术索引。 在数组A[0...n-1]中，有所谓的魔术索引，满足条件A[i] = i。给定一个有序整数数组，编写一种方法找出魔术索引，若有的话，在数组A中找出一个魔术索引，如果没有，则返回-1。若有多个魔术索引，返回索引值最小的一个。

示例1:

 输入：nums = [0, 2, 3, 4, 5]
 输出：0
 说明: 0下标的元素为0
示例2:

 输入：nums = [1, 1, 1]
 输出：1
说明:

nums长度在[1, 1000000]之间
此题为原书中的 Follow-up，即数组中可能包含重复元素的版本

*/

/* 思路:
 * 二分，剪枝，如果只有一个魔术值，则正常的二分法可以求解，
 * 如果存在多个魔术值，正常的二分法可能就失效了， 如 0 0 2
 * 这时就要分段讨论， [0, m), m, [m+1, size)
 * 如果 [0, m) 存在魔术值，则返回，递归求解左半侧
 * 如果 [0, m) 不存在魔术值，判断 m 是否为魔术值, 是则返回
 * 如果 m 不是魔术值，则判断 [m+1, size) 右侧是否存在，同样递归解决。
 */
class Solution {
public:
    int findMagicIndex(vector<int>& nums) {
        return GetAnswer(nums, 0, nums.size());
    }

    int GetAnswer(const vector<int>& nums, int start, int end) {
        if (end <= start) {
            return -1;
        }
        int m = start + (end - start) / 2;

        int left = GetAnswer(nums, start, m);
        if (left != -1) {
            return left;
        }

        if (nums[m] == m) {
            return m;
        }

        return GetAnswer(nums, m+1, end);
    }
};
