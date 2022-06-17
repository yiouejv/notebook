/*
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

 

示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
示例 2：

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 

限制：

0 <= matrix.length <= 100
0 <= matrix[i].length <= 100

*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return {};
        }
        if (m == 1) {
            return matrix[0];
        }

        vector<int> ans;
        int n = matrix[0].size();
        if (n == 1) {
            for (int i = 0; i < m; ++i) {
                ans.push_back(matrix[i][0]);
            }
            return ans;
        }

        int i = 0, j = 0;
        int level = 0;
        int count = m * n;
        while (i < m && j < n) {
            i = level, j = level;

            // 从左到右
            for (int k = 0; k < n - 2 * level - 1 && ans.size() < count; ++k) {
                ans.push_back(matrix[i][j++]);
            }

            // 从上到下
            for (int k = 0; k < m - 2 * level - 1 && ans.size() < count; ++k) {
                ans.push_back(matrix[i++][j]);
            }

            // 从右到左
            for (int k = j; k >= level + 1 && ans.size() < count; --k) {
                ans.push_back(matrix[i][j--]);
            }

            // 从下到上
            for (int k = i; k >= level + 1 && ans.size() < count; --k) {
                ans.push_back(matrix[i--][j]);
            }
            ++level;
        }
        if (ans.size() < count && count % 2) {
            ans.push_back(matrix[m / 2][n / 2]);
        }
        return ans;
    }
};
