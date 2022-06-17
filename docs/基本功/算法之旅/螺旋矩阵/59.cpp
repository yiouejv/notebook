/*

给你一个正整数 n ，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

 

示例 1：


输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
示例 2：

输入：n = 1
输出：[[1]]
 

提示：

1 <= n <= 20

*/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n, vector<int>(n, 0));
        int stop = n * n;
        int m = 0, level = 0;

        while (m < stop) {
            int i = level, j = level;

            // 从左到右
            for (int k = 0; k < n - 2*level - 1 && m < stop; ++k) {
                ans[i][j++] = ++m;
            }

            // 从上到下
            for (int k = 0; k < n - 2*level - 1 && m < stop; ++k) {
                ans[i++][j] = ++m;
            }

            // 从右到左
            for (int k = j; k >= level + 1 && m < stop; --k) {
                ans[i][j--] = ++m;
            }

            // 从下到上
            for (int k = i; k >= level + 1 && m < stop; --k) {
                ans[i--][j] = ++m;
            }

            // 奇数的最后一个元素直接设置
            if (m == stop - 1) {
                int idx = n / 2;
                ans[idx][idx] = stop;
                break;
            }
            ++level;
        }
        return ans;
    }
};
