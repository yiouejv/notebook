/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:

输入: nums = [1], k = 1
输出: [1]
 

提示：

1 <= nums.length <= 105
k 的取值范围是 [1, 数组中不相同的元素的个数]
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
 

进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。

*/


// 使用大顶堆，将元素根据出现的次数排序
// 取前k个元素作为答案
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int n : nums) {
            map[n]++;
        }

        typedef pair<int, int> elem;
        auto cmp = [](elem e1, elem e2) {
            return e1.second < e2.second;
        };
        priority_queue<elem, vector<elem>, decltype(cmp)> pq(cmp);

        for (auto [first, second] : map) {
            pq.push({first, second});
        }

        vector<int> ans;
        while (ans.size() < k) {
            elem e = pq.top();
            ans.push_back(e.first);
            pq.pop();
        }
        return ans;
    }
};


// 上述实现维护了所有的元素
// 优化: 只需维护k个元素即可
// 使用小顶堆，将最小的元素放在堆顶
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int n : nums) {
            map[n]++;
        }

        typedef pair<int, int> elem;
        auto cmp = [](elem e1, elem e2) {
            return e1.second > e2.second;
        };
        priority_queue<elem, vector<elem>, decltype(cmp)> pq(cmp);

        for (auto [first, second] : map) {
            pq.push({first, second});
            if (pq.size() > k) {
                pq.pop();
            }
        }

        vector<int> ans;
        while (ans.size() < k) {
            elem e = pq.top();
            ans.push_back(e.first);
            pq.pop();
        }
        return ans;
    }
};
