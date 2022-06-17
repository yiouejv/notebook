/*
给定一个 正整数 num ，编写一个函数，如果 num 是一个完全平方数，则返回 true ，否则返回 false 。

进阶：不要 使用任何内置的库函数，如  sqrt 。

 

示例 1：

输入：num = 16
输出：true
示例 2：

输入：num = 14
输出：false
 

提示：

1 <= num <= 2^31 - 1
*/

class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        int l = 0;
        int r = num - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            int sqrt = num / m;
            if (sqrt == m) {
                if (num % m == 0) return true;
                l = m + 1;
            } else if (sqrt < m) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return false;
    }
};
