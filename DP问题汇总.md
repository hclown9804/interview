[DP问题分类汇总-加强版](https://chengzhaoxi.xyz/42296.html)

# 线性DP

## 单串问题

### 单串LIS系列

#### [300. 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

```java
class Solution {
    public int lengthOfLIS(int[] nums) {
        int n = nums.length, ans = 0;
        int[] f = new int[n];
        for (int i = 0; i < n; ++i) {
            f[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) f[i] = Math.max(f[i], f[j] + 1);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}
```

### [673. 最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)

> ```
> 输入: [1,3,5,4,7]
> 输出: 2
> 解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
> ```

* $g[i]$：以 $i$ 结尾的最长上升子序列的个数

```java
class Solution {
    public int findNumberOfLIS(int[] nums) {
        int n = nums.length;
        int[] f = new int[n], g = new int[n];
        int maxLen = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            f[i] = g[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    if (f[i] < f[j] + 1) {
                        f[i] = f[j] + 1;
                        g[i] = g[j];
                    } 
                    else if (f[i] == f[j] + 1) g[i] += g[j];
                }
            }
            if (maxLen < f[i]) {
                maxLen = f[i];
                ans = g[i];
            }
            else if (maxLen == f[i]) ans += g[i];
        }
        return ans;
    }
}
```











