
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 1) {
            return matrix[0];
        }

        int n = matrix[0].size();
        if (n == 1) {
            vector<int> ans;
            for (int i = 0; i < m; ++i) {
                ans.push_back(matrix[i][0]);
            }
            return ans;
        }
        int count = m * n;
        int level = 0;
        int i = 0, j = 0;
        vector<int> ans;

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
        if (m * n % 2 && ans.size() < count) {
            ans.push_back(matrix[m / 2][n / 2]);
        }
        return ans;
    }
};
