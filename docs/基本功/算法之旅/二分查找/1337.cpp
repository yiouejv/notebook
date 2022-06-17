/*
给你一个大小为 m * n 的矩阵 mat，矩阵由若干军人和平民组成，分别用 1 和 0 表示。

请你返回矩阵中战斗力最弱的 k 行的索引，按从最弱到最强排序。

如果第 i 行的军人数量少于第 j 行，或者两行军人数量相同但 i 小于 j，那么我们认为第 i 行的战斗力比第 j 行弱。

军人 总是 排在一行中的靠前位置，也就是说 1 总是出现在 0 之前。

 

示例 1：

输入：mat = 
[[1,1,0,0,0],
 [1,1,1,1,0],
 [1,0,0,0,0],
 [1,1,0,0,0],
 [1,1,1,1,1]], 
k = 3
输出：[2,0,3]
解释：
每行中的军人数目：
行 0 -> 2 
行 1 -> 4 
行 2 -> 1 
行 3 -> 2 
行 4 -> 5 
从最弱到最强对这些行排序后得到 [2,0,3,1,4]
示例 2：

输入：mat = 
[[1,0,0,0],
 [1,1,1,1],
 [1,0,0,0],
 [1,0,0,0]], 
k = 2
输出：[0,2]
解释： 
每行中的军人数目：
行 0 -> 1 
行 1 -> 4 
行 2 -> 1 
行 3 -> 1 
从最弱到最强对这些行排序后得到 [0,2,3,1]
 

提示：

m == mat.length
n == mat[i].length
2 <= n, m <= 100
1 <= k <= m
matrix[i][j] 不是 0 就是 1

*/

/*
 * 思路: 遍历每一行，得到一个战力数组，一个小顶堆
 * 小顶堆用于得到较小战力，遍历数组寻找较小战力，得到行号
 *  求战力时可以利用二分查找，找到最后一个1的位置
 *
 * */
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<int> powerVec;
        priority_queue<int, vector<int>, greater<int>> pq;

        for(const vector<int>& nums : mat) {
            int power = GetRowPower(nums);
            powerVec.push_back(power);
            pq.push(power);
        }

        vector<int> ans;
        int rowCount = mat.size();
        while (ans.size() < k) {
            int target = pq.top();

            // delete all target from pq
            while (!pq.empty() && pq.top() == target) {
                pq.pop();
            }

            for (int i = 0; i < rowCount; ++i) {
                if (powerVec[i] == target) {
                    ans.push_back(i);

                    if (ans.size() >= k) {
                        return ans;
                    }
                }
            }
        }
        return ans;
    }

private:
    int GetRowPower(const vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        int right = -2;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] == 0) {
                r = m - 1;
            } else {
                l = m + 1;
                right = l;
            }
        }

        return right == -2 ? 0 : right;
    }
};
