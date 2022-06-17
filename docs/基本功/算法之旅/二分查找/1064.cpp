class Solution {
public:
    int fixedPoint(vector<int>& arr) {
        int l = 0;
        int r = arr.size() - 1;
        int minIndex = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (arr[m] == m) {
                if (minIndex == -1) {
                    minIndex = m;
                } else {
                    minIndex = min(minIndex, m);
                }
                r = m - 1;
            } else if (arr[m] > m) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return minIndex;
    }
};
