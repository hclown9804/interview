# 思路

* 每次将一个数放在正确的位置上

### 代码

```c++
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        for (auto x: nums) {
            if (x < 0 || x >= n) return -1;
        }
        for (int i = 0; i < n; ++i) {
            while (nums[nums[i]] != nums[i]) swap(nums[i], nums[nums[i]]);
            if (nums[i] != i) return nums[i];
        }
        return -1;
    }
};
```

