# CodeTop

## 字节跳动

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

* **滑动窗口**

维护一个滑动窗口，表示 从$i$  到 $j$ 的一个区间。扫描过程中维护一个哈希表，用来存储$[i, j]$ 中每个字符出现的次数。对其进行扫描时：

1.指针 $j$ 向后移动一步，同时计数加一；

2.假设 $j$ 移动前的区间 $[i,j]$ 中没有重复字符，则对于 $j$ 移动后，只有 $s[j]$ 可能出现2次。为了保证区间中每个字符只出现一次，因此需要将 $i$ 不断向后移动，直到满足条件；

3.更新 $ans$ 的结果。

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





