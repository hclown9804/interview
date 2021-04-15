# DFS

## 全排序类题目

* 有重复必须先排序，并且在循环中判断是否为第一次出现的数

### [46. 全排列](https://leetcode-cn.com/problems/permutations/)

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

### [47. 全排列 II](https://leetcode-cn.com/problems/permutations-ii/)

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

### [面试题 08.07. 无重复字符串的排列组合](https://leetcode-cn.com/problems/permutation-i-lcci/)

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

### [面试题 08.08. 有重复字符串的排列组合](https://leetcode-cn.com/problems/permutation-ii-lcci/)

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

### [60. 排列序列](https://leetcode-cn.com/problems/permutation-sequence/)

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

### [784. 字母大小写全排列](https://leetcode-cn.com/problems/letter-case-permutation/)

* 大小写转换

> ```
> 输入：S = "a1b2"
> 输出：["a1b2", "a1B2", "A1b2", "A1B2"]
> ```

```java
class Solution {
    List<String> ans = new ArrayList<>();
    public List<String> letterCasePermutation(String S) {
        dfs(S.toCharArray(), 0);
        return ans;
    }

    public void dfs(char s[], int u) {
        if (u == s.length) {
            ans.add(new String(s));
            return;
        }
        dfs(s, u + 1);
        if (Character.isLetter(s[u])) {
            s[u] ^= 32;
            dfs(s, u + 1);
            s[u] ^= 32;
        }
    }
}
```

## 组合类题目

### [17. 电话号码的字母组合](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)

```java
class Solution {
    Map<Character, String> map = new HashMap<Character, String>() {{
        put('2', "abc");
        put('3', "def");
        put('4', "ghi");
        put('5', "jkl");
        put('6', "mno");
        put('7', "pqrs");
        put('8', "tuv");
        put('9', "wxyz");
    }};
    List<String> ans = new ArrayList<>();
    StringBuilder sb = new StringBuilder();

    public void dfs(char[] s, int u) {
        int n = s.length;
        if (u == n) {
            ans.add(sb.toString());
            return;
        }
        String str = map.get(s[u]);
        for (int i = 0; i < str.length(); ++i) {
            sb.append(str.charAt(i));
            dfs(s, u + 1);
            sb.deleteCharAt(u);
        }
    }

    public List<String> letterCombinations(String digits) {
        if (digits.equals("")) return new ArrayList<String>();
        dfs(digits.toCharArray(), 0);
        return ans;
    } 
}
```

### [77. 组合](https://leetcode-cn.com/problems/combinations/)

> ```
> 输入: n = 4, k = 2
> 输出:
> [
>   [2,4],
>   [3,4],
>   [2,3],
>   [1,2],
>   [1,3],
>   [1,4],
> ]
> ```

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public void dfs(int n, int k, int u) {
        if (path.size() + (n - u + 1) < k) return;
        if (path.size() == k) {
            ans.add(new ArrayList<Integer>(path));
            return;
        }
        path.add(u);
        dfs(n, k, u + 1);
        path.remove(path.size() - 1);
        dfs(n, k, u + 1);
    }

    public List<List<Integer>> combine(int n, int k) {
        dfs(n, k, 1);
        return ans;
    }
}
```

### [39. 组合总和](https://leetcode-cn.com/problems/combination-sum/)

> ```
> 输入：candidates = [2,3,6,7], target = 7,
> 所求解集为：
> [
>   [7],
>   [2,2,3]
> ]
> ```

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public void dfs(int[] nums, int target, int u) {
        int n = nums.length;
        if (target == 0) {
            ans.add(new ArrayList<>(path));
            return;
        }
        if (u == n) return;
        for (int i = 0; nums[u] * i <= target; ++i) {
            dfs(nums, target - nums[u] * i, u + 1);
            path.add(nums[u]);
        }
        for (int i = 0; nums[u] * i <= target; ++i) path.remove(path.size() - 1);
    }

    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        dfs(candidates, target, 0);
        return ans;
    }
}
```

