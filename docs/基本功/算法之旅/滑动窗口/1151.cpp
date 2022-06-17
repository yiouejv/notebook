/*
给出一个二进制数组 data，你需要通过交换位置，将数组中 任何位置 上的 1 组合到一起，并返回所有可能中所需 最少的交换次数。
 

示例 1：

输入：[1,0,1,0,1]
输出：1
解释： 
有三种可能的方法可以把所有的 1 组合在一起：
[1,1,1,0,0]，交换 1 次；
[0,1,1,1,0]，交换 2 次；
[0,0,1,1,1]，交换 1 次。
所以最少的交换次数为 1。
示例 2：

输入：[0,0,0,1,0]
输出：0
解释： 
由于数组中只有一个 1，所以不需要交换。
示例 3：

输入：[1,0,1,0,1,0,0,1,1,0,1]
输出：3
解释：
交换 3 次，一种可行的只用 3 次交换的解决方案是 [0,0,0,0,0,1,1,1,1,1,1]。
 

提示：

1 <= data.length <= 10^5
0 <= data[i] <= 1

*/

/*
 * 思路: 把所有的1放在一起，利用一个固定大小的滑窗
 * 遍历data，找出滑窗中1的最大个数
 * 原数组中1的个数 - 1的最大数量
 */

class Solution {
public:
    int minSwaps(vector<int>& data) {
        int count1 = 0;
        for (int n : data) {
            if (n == 1) {
                ++count1;
            }
        }

        int size = data.size();
        int max1 = 0;
        int countWindow1 = 0;
        int i = 0, j = 0;

        while (j < size) {
            countWindow1 += data[j];
            if (j >= count1 - 1) {
                max1 = max(max1, countWindow1);
                countWindow1 -= data[i];
                ++i;
            }
            ++j;
        }
        return count1 - max1;
    }
};
