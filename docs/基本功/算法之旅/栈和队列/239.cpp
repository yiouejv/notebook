/*
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。

你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

 

示例 1：

输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：

输入：nums = [1], k = 1
输出：[1]
示例 3：

输入：nums = [1,-1], k = 1
输出：[1,-1]
示例 4：

输入：nums = [9,11], k = 2
输出：[11]
示例 5：

输入：nums = [4,-2], k = 2
输出：[4]
 

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length

*/


class Solution {
private:
    class MyQueue {
        public:
            int top() {
                return dq.front();
            }
            void pop() {
                dq.pop_front();
            }
            void push(int val) {
                while (!dq.empty() && val > dq.back()) {
                    dq.pop_back();
                }
                dq.push_back(val);
            }
            bool empty() {
                return dq.empty();
            }
        private:
            deque<int> dq;
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;  // 用来保存栈内的较大值
        // 拿出第一个滑动窗口，将数据入队
        vector<int> vec(nums.begin(), nums.begin() + k);
        for (int n : vec) {
            que.push(n);
        }

        vector<int> ans{que.top()};
        int i = 1, j;
        for (j = k; j < nums.size(); ++j) {
            if (!que.empty() && nums[i - 1] >= que.top()) {
                que.pop();
            }
            que.push(nums[j]);
            ans.push_back(que.top());
            ++i;
        }
        return ans;
    }
};
