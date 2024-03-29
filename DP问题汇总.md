

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

*Kanade 算法*

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

#### [152. 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray/)

> ```
> 输入: [2,3,-2,4]
> 输出: 6
> 解释: 子数组 [2,3] 有最大乘积 6。
> ```

* $f[i]$：以 $nums[i]$ 结尾的乘积最大值；
  * $nums[i]>0:f[i]=f[i-1]*nums[i]$
  * $nums[i]<0:f[i]=g[i-1]*nums[i]$
* $g[i]$：以 $nums[i]$ 结尾的乘积最小值；
  * $nums[i]>0:g[i]=g[i-1]*nums[i]$
  * $nums[i]<0:g[i]=f[i-1]*nums[i]$

```java
class Solution {
    public int maxProduct(int[] nums) {
        int n = nums.length;
        int ans = nums[0];
        int[] f = new int[n + 1], g = new int[n + 1];
        f[0] = g[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            int t = nums[i];
            if (nums[i] > 0) {
                f[i] = f[i - 1] * t;
                g[i] = g[i - 1] * t;
            }
            if (nums[i] < 0) {
                f[i] = g[i - 1] * t;
                g[i] = f[i - 1] * t;
            }
            f[i] = Math.max(t, Math.max(f[i], g[i]));
            g[i] = Math.min(t, Math.min(f[i], g[i]));
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}

class Solution {
    public int maxProduct(int[] nums) {
        int n = nums.length;
        int ans = nums[0], f = nums[0], g = nums[0];
        for (int i = 1; i < n; ++i) {
            int a = nums[i];
            int fa = f * a, ga = g * a;
            f = Math.max(a, Math.max(fa, ga));
            g = Math.min(a, Math.min(fa, ga));
            ans = Math.max(f, ans);
        }
        return ans;
    }
}
```

#### [918. 环形子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/)

> ```
> 输入：[3,-1,2,-1]
> 输出：4
> 解释：从子数组 [2,-1,3] 得到最大和 2 + (-1) + 3 = 4
> ```

* 两次 $Kadane$ 算法
* 不使用循环数组：直接使用 $Kadane$ 算法；
* 使用循环数组：必然包含首尾两个元素，因为求子数组最大值，则 $nums[1:n-1]$ 必定最小。

```java
class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int n = nums.length, max = nums[0], f = nums[0], sum = nums[0], min = 0;
        for (int i = 1; i < n; ++i) {
            sum += nums[i];
            f = nums[i] + Math.max(f, 0);
            max = Math.max(max, f);
        }
        f = nums[0];
        for (int i = 1; i < n - 1; ++i) {
            f = nums[i] + Math.min(f, 0);
            min = Math.min(min, f);
        }
        return Math.max(sum - min, max);
    }
}
```

#### [面试题 17.24. 最大子矩阵](https://leetcode-cn.com/problems/max-submatrix-lcci/)

> ```
> 输入：
> [[9,-8,1,3,-2],
> [-3,7,6,-2,4],
> [6,-4,-4,8,-7]]
> 输出：
> [0,0,2,3]
> ```

```java
class Solution {
    public int[] getMaxMatrix(int[][] matrix) {
        int n = matrix.length, m = matrix[0].length;
        int[][] sum = new int[n + 1][m + 1];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        int max = Integer.MIN_VALUE;
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < m; ++i) {
            for (int j = i; j < m; ++j) {
                for (int k = 0, pre = 0; k < n; ++k) {
                    int val = sum[k + 1][j + 1] - sum[k + 1][i] - sum[pre][j + 1] + sum[pre][i];
                    if (max < val) {
                        max = val;
                        ans = Arrays.asList(pre, i, k, j);
                    }
                    if (val <= 0) pre = k + 1;
                }
            }
        }
        return ans.stream().mapToInt(Integer::valueOf).toArray();
    }
}
```

#### [363. 矩形区域不超过 K 的最大数值和](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/)

> ```
> 输入：matrix = [[1,0,1],[0,-2,3]], k = 2
> 输出：2
> 解释：蓝色边框圈出来的矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/03/18/sum-grid.jpg)

```java
class Solution {
    public int maxSumSubmatrix(int[][] matrix, int k) {
        int n = matrix.length, m = matrix[0].length, ans = Integer.MIN_VALUE;
        int[][] sum = new int[n + 1][m + 1];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = i; j <= m; ++j) {
                TreeSet<Integer> set = new TreeSet<>();
                set.add(0);
                for (int t = 1; t <= n; ++t) {
                    int val = get(sum, 1, i, t, j);
                    Integer ceil = set.ceiling(val - k);
                    if (ceil != null) ans = Math.max(ans, val - ceil);
                    set.add(val);
                }
            }
        }
        return ans;
    }

    public int get(int[][] sum, int x1, int y1, int x2, int y2) {
        return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
    }
}
```

#### [1186. 删除一次得到子数组最大和](https://leetcode-cn.com/problems/maximum-subarray-sum-with-one-deletion/)

> ```
> 输入：arr = [1,-2,0,3]
> 输出：4
> 解释：我们可以选出 [1, -2, 0, 3]，然后删掉 -2，这样得到 [1, 0, 3]，和最大。
> ```

* $f[i][0]$：到第 $i$ 个元素没有删除操作的最大子数组之和；
* $f[i][1]$：到第 $i$ 个元素任意删除一次的最大子数组之和；

```java
class Solution {
    public int maximumSum(int[] arr) {
        int n = arr.length, ans = arr[0];
        int[][] f = new int[n][2];
        f[0][0] = arr[0];
        for (int i = 1; i < n; ++i) {
            f[i][0] = Math.max(f[i - 1][0] + arr[i], arr[i]);
            f[i][1] = Math.max(f[i - 1][1] + arr[i], f[i - 1][0]);
            ans = Math.max(ans, Math.max(f[i][0], f[i][1]));
        }
        return ans;
    }
}
```

* 删除 $k$ 次的到子数组最大和

```java
class Solution {
    public int maximumSum(int[] arr) {
        int n = arr.length;
        int k = 1, ans = arr[0];
        int[][] f = new int[n][k + 1];
        f[0][0] = arr[0];
        for (int i = 1; i < n; ++i) {
            f[i][0] = Math.max(f[i - 1][0] + arr[i], arr[i]);
            ans = Math.max(ans, f[i][0]);
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                f[i][j] = Math.max(f[i - 1][j] + arr[i], f[i - 1][j - 1]);
                ans = Math.max(ans, f[i][j]);
            }
        }
        return ans;
    }
}
```

#### [1191. K 次串联后最大子数组之和](https://leetcode-cn.com/problems/k-concatenation-maximum-sum/)

> ```
> 输入：arr = [1,-2,1], k = 5
> 输出：2
> ```

```java
class Solution {
    public int kConcatenationMaxSum(int[] arr, int k) {
        long max = arr[0] > 0 ? arr[0] : 0L, ans = max, sum = arr[0];
        int n = arr.length, MOD = 1000000007;
        for (int i = 1; i < Math.min(k, 2) * n; ++i) {
            max = Math.max(max + arr[i % n], arr[i % n]);
            ans = Math.max(ans, max);
            if (i < n) sum += arr[i];
        }
        while (sum > 0 && --k >= 2) ans = (ans + sum) % MOD;
        return (int)ans % MOD;
    }
}
```





















