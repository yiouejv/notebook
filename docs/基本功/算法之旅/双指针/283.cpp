/*
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

*/


class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int i = 0,
            j = 0;

        while (i < size && j < size) {
            while (i < size && nums[i] != 0) {
                ++i;
            }

            j = i + 1;
            while (j < size && nums[j] == 0) {
                ++j;
            }
            if (i < size && j < size) {
                swap(nums[i++], nums[j++]);
            }
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int i = 0;

        for (int n : nums) {
            if (n != 0) {
                nums[i++] = n;
            }
        }
        for (int j = i; j < size; j++) {
            nums[j] = 0;
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int j = 0;

        for (int i = 0; i < size; ++i) {
            if (nums[i] == 0) {
                j = i + 1;
                while (j < size && nums[j] == 0) {
                    ++j;
                }
                if (j < size) {
                    swap(nums[i], nums[j]);
                }
            }
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size();
        int i = 0,
            j = 0;

        while (j < size) {
            if (nums[j] != 0) {
                swap(nums[i], nums[j]);
                ++i;
            }
            ++j;
        }
    }
};
