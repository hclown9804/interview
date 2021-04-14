# DFS

## [46. 全排列](https://leetcode-cn.com/problems/permutations/)

* **没有重复**的数字序列

> 输入: [1,2,3]
> 输出:
> [
>   [1,2,3],
>   [1,3,2],
>   [2,1,3],
>   [2,3,1],
>   [3,1,2],
>   [3,2,1]
> ]

``` java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();
    boolean st[];

    public void dfs(int[] nums, int u) {
        if (u == nums.length) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = 0; i < nums.length; ++i) {
            if (!st[i]) {
                path.add(nums[i]);
                st[i] = true;
                dfs(nums, u + 1);
                path.remove(path.size() - 1);
                st[i] = false;
            }
        }
    }

    public List<List<Integer>> permute(int[] nums) {
        st = new boolean[nums.length];
        dfs(nums, 0);
        return ans;
    }
}
```

## [47. 全排列 II](https://leetcode-cn.com/problems/permutations-ii/)

* 可**包含重复数字**的序列

> ```
> 输入：nums = [1,1,2]
> 输出：
> [[1,1,2],
>  [1,2,1],
>  [2,1,1]]
> ```

 ```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();
    boolean st[];

    public void dfs(int[] nums, int u) {
        if (u == nums.length) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = 0; i < nums.length; ++i) {
            if (!st[i]) {
                if (i != 0 && nums[i - 1] == nums[i] && !st[i - 1]) continue;
                st[i] = true;
                path.add(nums[i]);
                dfs(nums, u + 1);
                st[i] = false;
                path.remove(path.size() - 1);
            }
        }
    }

    public List<List<Integer>> permuteUnique(int[] nums) {
        Arrays.sort(nums);
        st = new boolean[nums.length];
        dfs(nums, 0);
        return ans;
    }
}
 ```

## [面试题 08.07. 无重复字符串的排列组合](https://leetcode-cn.com/problems/permutation-i-lcci/)

* **无重复字符串**的排列组合

> ```
>  输入：S = "qwe"
>  输出：["qwe", "qew", "wqe", "weq", "ewq", "eqw"]
> ```

```java
class Solution {
    List<String> ans = new ArrayList<>();
    StringBuilder sb = new StringBuilder();
    boolean st[];

    public void dfs(char[] str, int u) {
        int n = str.length;
        if (u == n) {
            ans.add(sb.toString());
            return;        
        }
        for (int i = 0; i < n; ++i) {
            if (!st[i]) {
                sb.append(str[i]);
                st[i] = true;
                dfs(str, u + 1);
                st[i] = false;
                sb.deleteCharAt(sb.length() - 1);
            }
        }
    }

    public String[] permutation(String S) {
        st = new boolean[S.length()];
        dfs(S.toCharArray(), 0);
        String[] res = new String[ans.size()];
        for (int i = 0; i < ans.size(); ++i) res[i] = ans.get(i);
        return res;
    }
}
```

## [面试题 08.08. 有重复字符串的排列组合](https://leetcode-cn.com/problems/permutation-ii-lcci/)

* **有重复字符串**的排列组合

> ```
>  输入：S = "qqe"
>  输出：["eqq","qeq","qqe"]
> ```

```java
class Solution {
    List<String> ans = new ArrayList<>();
    StringBuilder sb = new StringBuilder();
    boolean st[];

    public void dfs(char[] str, int u) {
        int n = str.length;
        if (u == n) {
            ans.add(sb.toString());
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!st[i]) {
                if (i != 0 && str[i] == str[i - 1] && !st[i - 1]) continue;
                sb.append(str[i]);
                st[i] = true;
                dfs(str, u + 1);
                st[i] = false;
                sb.deleteCharAt(sb.length() - 1);
            }
        }
    }

    public String[] permutation(String S) {
        char[] str = S.toCharArray();
        Arrays.sort(str);
        st = new boolean[S.length()];
        dfs(str, 0);
        String[] res = new String[ans.size()];
        for (int i = 0; i < ans.size(); ++i) res[i] = ans.get(i);
        return res;
    }
}
```

## [1572. 递归实现指数型枚举 II](https://www.acwing.com/problem/content/1574/)

* 可包含重复数字的序列，从中随机选取任意多个数字

> ```
> 输入：3 1 2 2
> 输出：[ , 1, 2, 1 2, 2 2, 1 2 2]
> ```

```java
import java.util.*;

class Main {
    static boolean st[];

    public static void dfs(int[] nums, int u) {
        int n = nums.length;
        if (u == n) {
            for (int i = 0; i < n; ++i) {
                if (st[i]) System.out.print(nums[i] + " ");
            }
            System.out.println();
            return;
        }
        int k = u;
        while (k < n && nums[k] == nums[u]) k++;
        dfs(nums, k);
        for (int i = u; i < k; ++i) {
            st[i] = true;
            dfs(nums, k);
        }
        for (int i = u; i < k; ++i) st[i] = false;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int nums[] = new int[n];
        for (int i = 0; i < n; ++i) nums[i] = sc.nextInt();
        st = new boolean[n];
        Arrays.sort(nums);
        dfs(nums, 0);
    }
} 
```

## [93. 递归实现组合型枚举](https://www.acwing.com/problem/content/95/)

* 从 1∼n 这 n 个整数中随机选出 m 个

> ```
> 输入：5 3
> 输出：1 2 3 
>      1 2 4 
>      1 2 5 
>      1 3 4 
>      1 3 5 
>      1 4 5 
>      2 3 4 
>      2 3 5 
>      2 4 5 
>      3 4 5 
> ```

```java
import java.util.*;

class Main {
    static int n, m, N = 30;
    static int[] nums = new int[N];
    static boolean st[] = new boolean[N];
    
    public static void dfs(int u, int last) {
        if (u > m) {
            for (int i = 1; i <= m; ++i) System.out.print(nums[i] + " ");
            System.out.println();
            return;
        }
        for (int i = 1; i <= n; ++i) {
            if (!st[i] && i > last) {
                st[i] = true;
                nums[u] = i;
                dfs(u + 1, i);
                st[i] = false;
            }
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        nums[0] = 1;
        dfs(1, 0);
    }
}
```

## [1573. 递归实现组合型枚举 II](https://www.acwing.com/problem/content/1575/)

* 一个长度为 n 的可包含重复数字的序列，从中随机选取 m 个数字

> ```
> 输入：5 3
>      1 2 2 3 3
> 输出：1 2 2
>      1 2 3
>      1 3 3
>      2 2 3
>      2 3 3
> ```

```java
import java.util.*;

class Main {
    static int n, m;
    static boolean st[];
    // s:当前段选了几个数
    // u:当前一共选了几个数
    public static void dfs(int[] nums, int u, int s) {
        int n = nums.length;
        if (s > m) return;
        if (s == m) {
            for (int i = 0; i < u; ++i) {
                if (st[i]) System.out.print(nums[i] + " ");
            }
            System.out.println();
            return;
        }
        if (u == n) return;
        
        int k = u;
        while (k < n && nums[k] == nums[u]) {
            st[k++] = true;
            s++;
        }
        // 这一段全选
        dfs(nums, k, s);
        // 从大到小枚举 
        for (int i = k - 1; i >= u; --i) {
            st[i] = false;
            s--;
            dfs(nums, k, s);
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        m = sc.nextInt();
        int nums[] = new int[n];
        for (int i = 0; i < n; ++i) nums[i] = sc.nextInt();
        st = new boolean[n];
        Arrays.sort(nums);
        dfs(nums, 0, 0);
    }
} 
```

## [60. 排列序列](https://leetcode-cn.com/problems/permutation-sequence/)

* 第k个全排列序列

> ```
> 输入：n = 3, k = 3
> 输出："213"
> 
> _ _ _ 
> 一共三个位置，若第一个位置填1，则后面一共有(n - 1)!种即2种，小于k；
> 		    若第一个位置填2，则后面同样有2种，已经超过k，则第一个数字为2。
> ```

```java
class Solution {
    public String getPermutation(int n, int k) {
        String ans = "";
        boolean st[] = new boolean[10];
        for (int i = 0; i < n; ++i) {
            int fact = 1;
            for (int j = 1; j <= n - i - 1; ++j) fact *= j;
            for (int j = 1; j <= n; ++j) {
                if (!st[j]) {
                    if (fact < k) k -= fact;
                    else {
                        ans += Integer.toString(j);
                        st[j] = true;
                        break;
                    }
                }
            }
        }
        return ans;
    }
}
```

