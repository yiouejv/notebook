/*
给你两个整数数组 arr1 ， arr2 和一个整数 d ，请你返回两个数组之间的 距离值 。

「距离值」 定义为符合此距离要求的元素数目：对于元素 arr1[i] ，不存在任何元素 arr2[j] 满足 |arr1[i]-arr2[j]| <= d 。

 

示例 1：

输入：arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
输出：2
解释：
对于 arr1[0]=4 我们有：
|4-10|=6 > d=2 
|4-9|=5 > d=2 
|4-1|=3 > d=2 
|4-8|=4 > d=2 
所以 arr1[0]=4 符合距离要求

对于 arr1[1]=5 我们有：
|5-10|=5 > d=2 
|5-9|=4 > d=2 
|5-1|=4 > d=2 
|5-8|=3 > d=2
所以 arr1[1]=5 也符合距离要求

对于 arr1[2]=8 我们有：
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2
存在距离小于等于 2 的情况，不符合距离要求 

故而只有 arr1[0]=4 和 arr1[1]=5 两个符合距离要求，距离值为 2
示例 2：

输入：arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
输出：2
示例 3：

输入：arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6

提示：

1 <= arr1.length, arr2.length <= 500
-10^3 <= arr1[i], arr2[j] <= 10^3
0 <= d <= 100
*/


/*
 * 思路: 排序arr2, 利用二分找出|arr[i] - arr[j]| > d 的元素排除掉i, 否则i则是符合要求的
*/
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int count = 0;
        for (int n : arr1) {
            int isOk = InDistance(n, arr2, d);
            if (isOk) {
                ++count;
            }
        }
        return count;
    }
private:
    bool InDistance(int n, const vector<int>& nums, int d) {
        for (int i = 0; i < nums.size(); ++i) {
            if (abs(n - nums[i]) <= d) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count = count_if(arr1.begin(), arr1.end(), [&arr2, d] (int n) {
                auto it = lower_bound(arr2.begin(), arr2.end(), n - d);
                return (it == arr2.end()) || (*it > n + d);
            });
        return count;
    }
};
