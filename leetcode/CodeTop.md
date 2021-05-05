# CodeTop

### [3. 无重复字符的最长子串](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

> ```
> 输入: s = "abcabcbb"
> 输出: 3 
> 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
> 
> 输入: s = "bbbbb"
> 输出: 1
> 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
> 
> 输入: s = "pwwkew"
> 输出: 3
> 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
>      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
> ```

#### 思路：滑动窗口

维护一个滑动窗口，表示 从$i$  到 $j$ 的一个区间。扫描过程中维护一个哈希表，用来存储$[i, j]$ 中每个字符出现的次数。对其进行扫描时：

1.指针 $j$ 向后移动一步，同时计数加一；

2.假设 $j$ 移动前的区间 $[i,j]$ 中没有重复字符，则对于 $j$ 移动后，只有 $s[j]$ 可能出现2次。为了保证区间中每个字符只出现一次，因此需要将 $i$ 不断向后移动，直到满足条件；

3.更新 $ans$ 的结果。

时间复杂度：$O(N)$

```java

class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        int[] map = new int[128];
        int i = 0, j = 0, ans = 0;
        char[] str = s.toCharArray();
        while (j < n) {
            if (map[str[j]] > 0) i = Math.max(i, map[str[j]]);
            ans = Math.max(ans, j - i + 1);
            map[str[j]] = ++j;
        }
        return ans;
    }
}
```

### [718. 最长重复子数组](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/)

> ```
> 输入：
> A: [1,2,3,2,1]
> B: [3,2,1,4,7]
> 输出：3
> 解释：
> 长度最长的公共子数组是 [3, 2, 1] 。
> ```

#### 思路一：动态规划

1.状态表示：$f[i,j]$ 表示以 $nums1[i]$ 和 $nums2[j]$ 结尾的最长公共子数组的长度；

2.状态计算：如果 $nums1[i-1]==nums2[j-1]$ ，则对 $f[i,j]$ 的状态进行转移；

3.最终的答案为 $f[i,j]$ 的最大值。

时间复杂度：$O(N*M)$

```java
// 二维表示
class Solution {
    public int findLength(int[] nums1, int[] nums2) {
        int n = nums1.length, m = nums2.length, ans = 0;
        int[][] f = new int[n + 1][m + 1];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
                else f[i][j] = 0;
                ans = Math.max(ans, f[i][j]);
            }
        }
        return ans;    
    }
}

// 一维表示
// f[i][j]只依赖上一行上一列对角的值，因此只需要滚动数组存储
// 但是此时内层循环需要从大到小枚举，因为后面的值依赖前面的值，可以先更新
class Solution {
    public int findLength(int[] nums1, int[] nums2) {
        int n = nums1.length, m = nums2.length, ans = 0;
        int[] f = new int[m + 1];
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= 1; --j) {
                if (nums1[i - 1] == nums2[j - 1]) f[j] = f[j - 1] + 1;
                else f[j] = 0;
                ans = Math.max(ans, f[j]);
            }
        }
        return ans;
    }
}
```

#### 思路二：滑动窗口

1.枚举 $nums1$ 和 $nums2$ 的对齐方式：第一种 $nums1$ 不变， $nums2$ 的首元素与 $nums1$ 中的某个元素对齐；第一种 $nums2$ 不变， $nums1$ 的首元素与 $nums2$ 中的某个元素对齐。

2.对于每一种对齐方式，计算相对位置的重复子数组长度。

时间复杂度：$O(N+M)*min(N,M)$

```java
class Solution {
    public int findLength(int[] nums1, int[] nums2) {
        int n = nums1.length, m = nums2.length, ans = 0;
        for (int i = 0; i < n; ++i) {
            int len = Math.min(m, n - i);
            int maxLen = getMaxLen(nums1, nums2, i, 0, len);
            ans = Math.max(ans, maxLen);
        }
        for (int i = 0; i < m; ++i) {
            int len = Math.min(n, m - i);
            int maxLen = getMaxLen(nums1, nums2, 0, i, len);
            ans = Math.max(ans, maxLen);
        }
        return ans;
    }

    public int getMaxLen(int[] nums1, int[] nums2, int i1, int i2, int len) {
        int ans = 0, k = 0;
        for (int i = 0; i < len; ++i) {
            if (nums1[i1 + i] == nums2[i2 + i]) k++;
            else k = 0;
            ans = Math.max(ans, k);
        }
        return ans;
    }
}
```

#### 思路三：哈希+二分

1.将数组看成字符串，进行哈希，看作是 $p$ 进制数（$p$ 一般取 131）；

2.对 $nums1$ 和 $nums2$ 进行预处理；

3.如果 $nums1$ 和 $nums2$  有一个长度为  $k$ 的公共子数组，那么一定有长度小于等于 $k$  的公共子数组，则可以对其进行二分找到最大值。对数组进行二分，确定 $mid$ ，将 $nums1$ 中长度是 $mid$  的哈希值存入 $Set$ ，然后遍历 $nusm2$ 中长度是 $mid$ 的哈希值是否存在。

时间复杂度：$O(NlogN)$

```java
class Solution {
    int P = 131, n, m;
    long[] ha, hb, p;
    public int findLength(int[] nums1, int[] nums2) {
        n = nums1.length;
        m = nums2.length;
        ha = new long[n + 1];
        hb = new long[m + 1];
        p = new long[n + 1];
        p[0] = 1;
        for (int i = 1; i <= n; ++i) {
            ha[i] = ha[i - 1] * P + nums1[i - 1];
            p[i] = p[i - 1] * P;
        }
        for (int i = 1; i <= m; ++i) hb[i] = hb[i - 1] * P + nums2[i - 1];
        int l = 0, r = n;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        return l;
    }

    public boolean check(int mid) {
        HashSet<Long> set = new HashSet<>();
        for (int i = mid; i <= n; ++i) set.add(get(ha, i - mid + 1, i));
        for (int i = mid; i <= m; ++i) {
            if (set.contains(get(hb, i - mid + 1, i))) return true;
        }
        return false;
    }

    public long get(long[] h, int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
}
```



































