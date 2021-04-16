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
            sb.deleteCharAt(sb.length() - 1);
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
        // 剪枝
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

* 无重复数字且可以重复使用

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

### [40. 组合总和 II](https://leetcode-cn.com/problems/combination-sum-ii/)

* 数字可重复且只能用一次

> ```
> 输入: candidates = [10,1,2,7,6,1,5], target = 8,
> 所求解集为:
> [
>   [1, 7],
>   [1, 2, 5],
>   [2, 6],
>   [1, 1, 6]
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

        int k = u + 1;
        while (k < n && nums[k] == nums[u]) k++;
        int cnt = k - u;

        for (int i = 0; nums[u] * i <= target && i <= cnt; ++i) {
            dfs(nums, target - nums[u] * i, k);
            path.add(nums[u]);
        }
        for (int i = 0; nums[u] * i <= target && i <= cnt; ++i) path.remove(path.size() - 1);
    }

    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        dfs(candidates, target, 0);
        return ans;
    }
}
```

### [216. 组合总和 III](https://leetcode-cn.com/problems/combination-sum-iii/)

* 1-9 九个数字选取k个数，不能重复使用

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();
    int len = 9;

    public void dfs(int k, int target, int u, int sum) {
        if (path.size() + (len - u + 1) < k || path.size() > k) return;
        if (target == sum && path.size() == k) {
            ans.add(new ArrayList<>(path));
            return;
        }
        path.add(u);
        sum += u;
        dfs(k, target, u + 1, sum);
        path.remove(path.size() - 1);
        sum -= u;
        dfs(k, target, u + 1, sum);
    }

    public List<List<Integer>> combinationSum3(int k, int n) {
        dfs(k, n, 1, 0);
        return ans;
    }
}
```

### [377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/)

* 非DFS问题
* f[j] 表示总和为j的所有方案数

```java
class Solution {
    public int combinationSum4(int[] nums, int target) {
        int n = nums.length;
        int[] f = new int[target + 1];
        f[0] = 1;
        for (int j = 0; j <= target; ++j) {
            for (int x: nums) {
                if (j >= x) f[j] += f[j - x];
            }
        }
        return f[target];
    }
}
```

## 子集类题目

### [78. 子集](https://leetcode-cn.com/problems/subsets/)

> ```
> 输入：nums = [1,2,3]
> 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
> ```

```java
class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        int n = nums.length;
        for (int i = 0; i < 1 << n; ++i) {
            List<Integer> path = new ArrayList<>();
            for (int j = 0; j < n; ++j) {
                if ((i >> j & 1) == 1) path.add(nums[j]);
            }
            ans.add(path);
        }
        return ans;
    }
}
```

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public void dfs(int[] nums, int u) {
        if (u == nums.length) {
            ans.add(new ArrayList<>(path));
            return;
        }
        path.add(nums[u]);
        dfs(nums, u + 1);
        path.remove(path.size() - 1);
        dfs(nums, u + 1);
    }

    public List<List<Integer>> subsets(int[] nums) {
        dfs(nums, 0);
        return ans;
    }
}
```

### [90. 子集 II](https://leetcode-cn.com/problems/subsets-ii/)

> ```
> 输入：nums = [1,2,2]
> 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
> ```

```java
class Solution {
    private List<List<Integer>> ans = new ArrayList<>();
    private boolean[] st;

    public void dfs(int u, int[] nums) {
        int n = nums.length;
        if (u == n) {
            List<Integer> path = new ArrayList<>();
            for (int i = 0; i < n; ++i) {
                if (st[i]) path.add(nums[i]);
            }
            ans.add(path);
            return;
        }
        int k = u;
        while (k < n && nums[k]== nums[u]) k++;
        dfs(k, nums);

        for (int i = u; i < k; ++i) {
            st[i] = true;
            dfs(k, nums);
        }

        for (int i = u; i < k; ++i) st[i] = false;
    }

    public List<List<Integer>> subsetsWithDup(int[] nums) {
        st = new boolean[nums.length];
        Arrays.sort(nums);
        dfs(0, nums);
        return ans;
    }
}
```

## 单词搜索类题目

### [79. 单词搜索](https://leetcode-cn.com/problems/word-search/)

> 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
> 输出：true
>
> ![img](https://assets.leetcode.com/uploads/2020/11/04/word2.jpg)

```java
class Solution {
    int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

    public boolean dfs(char[][] board, String word, int u, int x, int y) {
        if (board[x][y] != word.charAt(u)) return false;
        if (u == word.length() - 1) return true;

        char t = board[x][y];
        board[x][y] = '.';
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= board.length || b < 0 || b >= board[0].length || board[a][b] == '.') continue;
            if (dfs(board, word, u + 1, a, b)) return true;
        }
        board[x][y] = t;
        return false;
    }

    public boolean exist(char[][] board, String word) {
        int n = board.length;
        if (n == 0) return false;
        int m = board[0].length;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dfs(board, word, 0, i, j)) return true;
            }
        }
        return false;
    }
}
```

### [212. 单词搜索 II](https://leetcode-cn.com/problems/word-search-ii/)

> 输入：board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
> 输出：["eat","oath"]
>
> ![img](https://assets.leetcode.com/uploads/2020/11/07/search1.jpg)

```java
class Solution {
    class Node {
        Node son[];
        int id;
        public Node() {
            id = -1;
            son = new Node[26];
        }
    }

    Node root = new Node();
    public void insert(String word, int id) {
        Node cur = root;
        for (char c: word.toCharArray()) {
            int u = c - 'a';
            if (cur.son[u] == null) cur.son[u] = new Node();
            cur = cur.son[u];
        }
        cur.id = id; 
    }

    int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
    Set<Integer> ids = new HashSet<>();
    public void dfs(char[][] board, int x, int y, Node cur) {
        if (cur.id != -1) ids.add(cur.id);
        char t = board[x][y];
        board[x][y] = '.';
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= board.length || b < 0 || b >= board[0].length || board[a][b] == '.') continue;
            int u = board[a][b] - 'a';
            if (cur.son[u] != null) dfs(board, a, b, cur.son[u]);
        }
        board[x][y] = t;
    }

    public List<String> findWords(char[][] board, String[] words) {
        for (int i = 0; i < words.length; ++i) insert(words[i], i);
        for (int i = 0; i < board.length; ++i) {
            for (int j = 0; j < board[i].length; ++j) {
                int u = board[i][j] - 'a';
                if (root.son[u] != null) dfs(board, i, j, root.son[u]);
            }
        }
        List<String> ans = new ArrayList<>();
        for (Integer id: ids) ans.add(words[id]);
        return ans;
    }
}
```

