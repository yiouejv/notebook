class Solution {
public:
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {
        int aliceCount = 0;
        for (int n : aliceSizes) {
            aliceCount += n;
        }

        int bobCount = 0;
        for (int n : bobSizes) {
            bobCount += n;
        }

        int aliceSize = aliceSizes.size();
        int bobSize = bobSizes.size();
        int i = 0;
        int j = 0;

        while (i < aliceSize) {
            int aliceValue = aliceSizes[i++];
            int j = 0;
            while (j < bobSize) {
                int bobValue = bobSizes[j++];
                if (aliceCount - aliceValue + bobValue == bobCount + aliceValue - bobValue) {
                    return {aliceValue, bobValue};
                }
            }
        }
        return {-1, -1};
    }
};
