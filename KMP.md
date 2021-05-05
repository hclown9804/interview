# KMP

* [28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

```java
class Solution {
    public int[] getNext(char[] s, int n) {
        int[] next = new int[n + 1];
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j > 0 && s[j + 1] != s[i]) j = next[j];
            if (s[j + 1] == s[i]) j++;
            next[i] = j;
        }
        return next;
    }

    public int strStr(String haystack, String needle) {
        int n1 = haystack.length(), n2 = needle.length();
        if (n2 == 0) return 0;
        haystack = " " + haystack;
        needle = " " + needle;
        char[] p = haystack.toCharArray();
        char[] s = needle.toCharArray();

        int[] next = getNext(s, n2);
        for (int i = 1, j = 0; i <= n1; ++i) {
            while (j > 0 && p[i] != s[j + 1]) j = next[j];
            if (p[i] == s[j + 1]) j++;
            if (j == n2) return i - n2;
        }
        return -1;
    }
}
```

