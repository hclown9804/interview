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

#### [673. 最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)

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

#### [354. 俄罗斯套娃信封问题](https://leetcode-cn.com/problems/russian-doll-envelopes/)

> ```
> 输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
> 输出：3
> 解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
> ```

```java
class Solution {
    public int maxEnvelopes(int[][] envelopes) {
        int n = envelopes.length;
        if (n == 0) return n;
        Arrays.sort(envelopes, (a, b)->(a[0] - b[0]));
        int[] f = new int[n];
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            f[i] = 1;
            for (int j = 0; j < n; ++j) {
                if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1]) f[i] = Math.max(f[i], f[j] + 1);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}
```

#### [1626. 无矛盾的最佳球队](https://leetcode-cn.com/problems/best-team-with-no-conflicts/)

> ```
> 输入：scores = [4,5,6,5], ages = [2,1,2,1]
> 输出：16
> 解释：最佳的选择是后 3 名球员。注意，你可以选中多个同龄球员。
> ```

```java
class Solution {
    public int bestTeamScore(int[] scores, int[] ages) {
        int n = scores.length;
        int[][] nums = new int[n][2];
        for (int i = 0; i < n; ++i) {
            nums[i][0] = ages[i];
            nums[i][1] = scores[i];
        }
        Arrays.sort(nums, new Comparator<int[]>() {
            public int compare(int[] a, int[] b) {
                if (a[0] == b[0]) return a[1] - b[1];
                return a[0] - b[0];
            }
        });
        int[] f = new int[n];
        for (int i = 0; i < n; ++i) f[i] = nums[i][1];
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j][1] <= nums[i][1]) f[i] = Math.max(f[i], f[j] + nums[i][1]);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}
```

#### [1048. 最长字符串链](https://leetcode-cn.com/problems/longest-string-chain/)

> ```
> 输入：["a","b","ba","bca","bda","bdca"]
> 输出：4
> 解释：最长单词链之一为 "a","ba","bda","bdca"。
> ```

```java
class Solution {
    public int longestStrChain(String[] words) {
        Arrays.sort(words, (a, b)->(a.length() - b.length()));
        int n = words.length;
        int[] f = new int[n];
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            f[i] = 1;
            String a = words[i];
            for (int j = 0; j < i; ++j) {
                String b = words[j];
                if (check(b, a)) f[i] = Math.max(f[i], f[j] + 1);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }

    public boolean check(String a, String b) {
        int n = a.length(), m = b.length();
        if (n != m - 1) return false;
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (a.charAt(i) == b.charAt(j)) i++;
            j++;
        }
        return i == n;
    }
}
```

#### [646. 最长数对链](https://leetcode-cn.com/problems/maximum-length-of-pair-chain/)

> ```
> 输入：[[1,2], [2,3], [3,4]]
> 输出：2
> 解释：最长的数对链是 [1,2] -> [3,4]
> ```

```java
class Solution {
    public int findLongestChain(int[][] pairs) {
        Arrays.sort(pairs, (a, b)->(a[0] - b[0]));
        int n = pairs.length, ans = 0;
        int[] f = new int[n];
        for (int i = 0; i < n; ++i) {
            f[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (pairs[j][1] < pairs[i][0]) f[i] = Math.max(f[i], f[j] + 1);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}
```

###  最大子串和系列

#### [3. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

> ```
> 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
> 输出：6
> 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
> ```

```java
class Solution {
    public int maxSubArray(int[] nums) {
        int n = nums.length, ans = Integer.MIN_VALUE;
        for (int i = 0, sum = 0; i < n; ++i) {
            sum = nums[i] + Math.max(0, sum);
            ans = Math.max(ans, sum);
        }
        return ans;
    }
}
```

