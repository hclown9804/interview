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

# BFS

## 网格类题目

### [130. 被围绕的区域](https://leetcode-cn.com/problems/surrounded-regions/)

> ```
> 输入: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
> 输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
> 解释：被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/02/19/xogrid.jpg)

```java
class Solution {
    public void solve(char[][] board) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        int n = board.length;
        if (n == 0) return;
        int m = board[0].length;
        Queue<int[]> queue = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            if (board[i][0] == 'O') queue.offer(new int[]{i, 0});
            if (board[i][m - 1] == 'O') queue.offer(new int[]{i, m - 1});
        }
        for (int i = 1; i < m - 1; ++i) {
            if (board[0][i] == 'O') queue.offer(new int[]{0, i});
            if (board[n - 1][i] == 'O') queue.offer(new int[]{n - 1, i});
        }
        while (!queue.isEmpty()) {
            int[] t = queue.poll();
            int x = t[0], y = t[1];
            board[x][y] = '.';
            for (int i = 0; i < 4; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (a < 0 || a >= n || b < 0 || b >= m || board[a][b] != 'O') continue;
                queue.offer(new int[]{a, b});
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == '.') board[i][j] = 'O';
                else if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
}
```

### [200. 岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)

> ```
> 输入：grid = [
>       ["1","1","1","1","0"],
>       ["1","1","0","1","0"],
>       ["1","1","0","0","0"],
>       ["0","0","0","0","0"]
>     ]
> 输出：1
> ```

```java
class Solution {
    public int numIslands(char[][] grid) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1') {
                    ++ans;
                    grid[i][j] = '0';
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    while (!queue.isEmpty()) {
                        int[] t = queue.poll();
                        int x = t[0], y = t[1];
                        for (int k = 0; k < 4; ++k) {
                            int a = x + dx[k], b = y + dy[k];
                            if (a < 0 || a >= n || b < 0 || b >= m || grid[a][b] == '0') continue;
                            queue.offer(new int[]{a, b});
                            grid[a][b] = '0';
                        }
                    }
                }
            }
        }
        return ans;
    }
}
```

### [695. 岛屿的最大面积](https://leetcode-cn.com/problems/max-area-of-island/)

> ```
> 输入：[[0,0,1,0,0,0,0,1,0,0,0,0,0],
>      [0,0,0,0,0,0,0,1,1,1,0,0,0],
>      [0,1,1,0,1,0,0,0,0,0,0,0,0],
>      [0,1,0,0,1,1,0,0,1,0,1,0,0],
>      [0,1,0,0,1,1,0,0,1,1,1,0,0],
>      [0,0,0,0,0,0,0,0,0,0,1,0,0],
>      [0,0,0,0,0,0,0,1,1,1,0,0,0],
>      [0,0,0,0,0,0,0,1,1,0,0,0,0]]
> 
> 输出：6
> ```
>
> ![](https://i.loli.net/2021/04/19/xOSNjQzv84dkmpr.png)

```java
class Solution {
    public int maxAreaOfIsland(int[][] grid) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    int tmp = 0;
                    while (!queue.isEmpty()) {
                        int[] t = queue.poll();
                        int x = t[0], y = t[1];
                        tmp++;
                        for (int k = 0; k < 4; ++k) {
                            int a = x + dx[k], b = y + dy[k];
                            if (a < 0 || a >= n || b < 0 || b >= m || grid[a][b] == 0) continue;
                            queue.offer(new int[]{a, b});
                            grid[a][b] = 0;
                        }
                    }
                    ans = Math.max(ans, tmp);
                }
            }
        }
        return ans;
    }
}
```

### [面试题 16.19. 水域大小](https://leetcode-cn.com/problems/pond-sizes-lcci/)

> ```
> 输入：
> [
>   [0,2,1,0],
>   [0,1,0,1],
>   [1,1,0,1],
>   [0,1,0,1]
> ]
> 输出： [1,2,4]
> ```

* 此题与上面的题目不同，需要判断周围8个点的坐标，而不是上下左右四个。

```java
class Solution {
    public int[] pondSizes(int[][] land) {
        int n = land.length;
        if (n == 0) return new int[]{};
        int m = land[0].length;
        List<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (land[i][j] == 0) {
                    int tmp = 0;
                    land[i][j] = 1;
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    while (!queue.isEmpty()) {
                        int[] t = queue.poll();
                        int x = t[0], y = t[1];
                        tmp++;
                        for (int k1 = x - 1; k1 <= x + 1; ++k1) {
                            for (int k2 = y - 1; k2 <= y + 1; ++k2) {
                                if (k1 == x && k2 == y) continue;
                                if (k1 < 0 || k1 >= n || k2 < 0 || k2 >= m || land[k1][k2] != 0) continue;
                                land[k1][k2] = 1;
                                queue.offer(new int[]{k1, k2});
                            }
                        }
                    }
                    ans.add(tmp);
                }
            }
        }
        int[] res = ans.stream().mapToInt(Integer::valueOf).toArray();
        Arrays.sort(res);
        return res;
    }
}
```

### [1162. 地图分析](https://leetcode-cn.com/problems/as-far-from-land-as-possible/)

> ```
> 输入：[[1,0,1],
> 	  [0,0,0],
> 	  [1,0,1]]
> 输出：2
> 解释： 
> 海洋单元格 (1, 1) 和所有陆地单元格之间的距离都达到最大，最大距离为 2
> ```

```java
class Solution {
    public int maxDistance(int[][] grid) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = -1;
        Queue<int[]> queue = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) queue.offer(new int[]{i, j});
            }
        }
        if (queue.size() == n * n) return -1;
        while (!queue.isEmpty()) {
            ans++;
            int size = queue.size();
            while (size-- > 0) {
                int[] t = queue.poll();
                int x = t[0], y = t[1];
                for (int i = 0; i < 4; ++i) {
                    int a = x + dx[i], b = y + dy[i];
                    if (a < 0 || a >= n || b < 0 || b >= m || grid[a][b] != 0) continue;
                    queue.offer(new int[]{a, b});
                    grid[a][b] = 2;
                }
            }
        }
        return ans;
    }
}
```

### [994. 腐烂的橘子](https://leetcode-cn.com/problems/rotting-oranges/)

> ```
> 输入：[[2,1,1],[1,1,0],[0,1,1]]
> 输出：4
> ```

```java
class Solution {
    public int orangesRotting(int[][] grid) {
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = 0, cnt = 0;
        Queue<int[]> queue = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 2) queue.offer(new int[]{i, j});
                else if (grid[i][j] == 1) cnt++;
            }
        }

        if (cnt == 0) return 0;

        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        while (!queue.isEmpty()) {
            ans++;
            int size = queue.size();
            while (size-- > 0) {
                int[] t = queue.poll();
                int x = t[0], y = t[1];
                for (int i = 0; i < 4; ++i) {
                    int a = x + dx[i], b = y + dy[i];
                    if (a >= 0 && a < n && b >= 0 && b < m && grid[a][b] == 1) {
                        cnt--;
                        grid[a][b] = 2;
                        queue.offer(new int[]{a, b});
                    }
                }
            }
        }
        return cnt == 0 ? ans - 1 : -1;
    }
}
```

## 课程表类题目

### [207. 课程表](https://leetcode-cn.com/problems/course-schedule/)

> ```
> 输入：numCourses = 2, prerequisites = [[1,0]]
> 输出：true
> 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
> ```

````java
class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        int[] indegrees = new int[numCourses];
        List<List<Integer>> adjacency = new ArrayList<>();
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numCourses; ++i) adjacency.add(new ArrayList<>());
        for (int[] pre: prerequisites) {
            indegrees[pre[0]]++;
            adjacency.get(pre[1]).add(pre[0]);
        } 

        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) queue.offer(i);
        }
        while (!queue.isEmpty()) {
            int t = queue.poll();
            numCourses--;
            for (int cur: adjacency.get(t)) {
                if (--indegrees[cur] == 0) queue.offer(cur);
            }
        }
        return numCourses == 0;
    }
}
````

### [210. 课程表 II](https://leetcode-cn.com/problems/course-schedule-ii/)

> ```
> 输入: 4, [[1,0],[2,0],[3,1],[3,2]]
> 输出: [0,1,2,3] or [0,2,1,3]
> 解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
>      因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
> ```

```java
class Solution {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        int[] indegrees = new int[numCourses];
        for (int[] pre: prerequisites) indegrees[pre[0]]++;
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) queue.offer(i);
        }
        int cnt = 0;
        int[] ans = new int[numCourses];
        while (!queue.isEmpty()) {
            int t = queue.poll();
            ans[cnt++] = t;
            for (int[] cur: prerequisites)  {
                if (cur[1] == t && --indegrees[cur[0]] == 0) queue.offer(cur[0]);
            }
        }
        if (cnt == numCourses) return ans;
        return new int[0];
    }
}
```

## 染色类

### [733. 图像渲染](https://leetcode-cn.com/problems/flood-fill/)

> ```
> 输入: 
>     image = [[1,1,1],[1,1,0],[1,0,1]]
>     sr = 1, sc = 1, newColor = 2
> 输出: [[2,2,2],[2,2,0],[2,0,1]]
> 解析: 
>     在图像的正中间，(坐标(sr,sc)=(1,1)),
>     在路径上所有符合条件的像素点的颜色都被更改成2。
>     注意，右下角的像素没有更改为2，
>     因为它不是在上下左右四个方向上与初始点相连的像素点。
> ```

```java
class Solution {
    public int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        int n = image.length;
        if (n == 0) return image;
        int m = image[0].length;
        int c = image[sr][sc];
        if (c == newColor) return image;

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{sr, sc});
        image[sr][sc] = newColor;
        while (!queue.isEmpty()) {
            int[] t = queue.poll();
            int x = t[0], y = t[1];
            for (int i = 0; i < 4; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (a < 0 || a >= n || b < 0 || b >= m || image[a][b] != c) continue;
                image[a][b] = newColor;
                queue.offer(new int[]{a, b});
            }
        }
        return image;
    }
}
```

### [1042. 不邻接植花](https://leetcode-cn.com/problems/flower-planting-with-no-adjacent/)

> ```
> 输入：n = 3, paths = [[1,2],[2,3],[3,1]]
> 输出：[1,2,3]
> 解释：
> 花园 1 和 2 花的种类不同。
> 花园 2 和 3 花的种类不同。
> 花园 3 和 1 花的种类不同。
> 因此，[1,2,3] 是一个满足题意的答案。其他满足题意的答案有 [1,2,4]、[1,4,2] 和 [3,2,1]
> ```

```java
class Solution {
    public int[] gardenNoAdj(int n, int[][] paths) {
        int[] ans = new int[n];
        List<List<Integer>> adjacency = new ArrayList<>();
        for (int i = 0; i <= n; ++i) adjacency.add(new ArrayList<>());
        for (int[] cur: paths) {
            adjacency.get(cur[0]).add(cur[1]);
            adjacency.get(cur[1]).add(cur[0]);
        }
        for (int i = 1; i <= n; ++i) {
            boolean[] color = new boolean[5];
            for (int id: adjacency.get(i)) color[ans[id - 1]] = true;
            for (int j = 1; j <= 4; ++j) {
                if (!color[j]) {
                    ans[i - 1] = j;
                    break;
                }
            }
        }
        return ans;
    }
}
```

# 链表

## 链表基础

### 自定义链表

```java
public class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) {this.val = val;}
    ListNode(int val, ListNode next) {this.val = val; this.next = next;}
} 
```

### 生成链表

```java
    public static ListNode createList(int[] nums) {
        ListNode dummy = new ListNode(-1);
        ListNode cur = dummy;
        for (int num: nums) {
            cur = cur.next = new ListNode(num);
        }
        return dummy.next;
    }

    public static ListNode createRandomList(int n) {
        ListNode dummy = new ListNode(-1);
        ListNode cur = dummy;
        Random random = new Random();
        while (n-- > 0){
            cur = cur.next = new ListNode(random.nextInt() % 1001);
        }
        return dummy.next;
    }
```

### 输出链表

```java
    public static void printList(ListNode head) {
        while (head != null) {
            if (head.next != null) System.out.print(head.val + "->");
            else System.out.print(head.val);
            head = head.next;
        }
        System.out.println();
    }
    @Override
    public String toString() {
        ListNode cur = this;
        StringBuilder sb = new StringBuilder();
        while (cur != null) {
            sb.append(cur.val);
            if (cur.next != null) sb.append("->");
            cur = cur.next;
        }
        return sb.toString();
    }

```

## 加法题

### [2. 两数相加](https://leetcode-cn.com/problems/add-two-numbers/)

> ```
> 输入：l1 = [2,4,3], l2 = [5,6,4]
> 输出：[7,0,8]
> 解释：342 + 465 = 807.
> ```

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(-1);
        ListNode cur = dummy;
        int c = 0;
        while (l1 != null || l2 != null) {
            int a = l1 == null ? 0 : l1.val;
            int b = l2 == null ? 0 : l2.val;
            int t = a + b + c;
            cur = cur.next = new ListNode(t % 10);
            c = t / 10;
            if (l1 != null) l1 = l1.next;
            if (l2 != null) l2 = l2.next;
        }
        if (c == 1) cur.next = new ListNode(1);
        return dummy.next;
    }
}
```

### [445. 两数相加 II](https://leetcode-cn.com/problems/add-two-numbers-ii/)

> ```
> 输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
> 输出：7 -> 8 -> 0 -> 7
> ```

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        Stack<Integer> s1 = new Stack<>();
        Stack<Integer> s2 = new Stack<>();      
        while (l1 != null) {
            s1.push(l1.val);
            l1 = l1.next;
        }
        while (l2 != null) {
            s2.push(l2.val);
            l2 = l2.next;
        }
        ListNode cur = null;
        int c = 0;
        while (!s1.isEmpty() || !s2.isEmpty() || c != 0) {
            int a = s1.isEmpty() ? 0 : s1.pop();
            int b = s2.isEmpty() ? 0 : s2.pop();

            int t = a + b + c;
            c = t / 10; 
            ListNode tmp = new ListNode(t % 10);
            tmp.next = cur;
            cur = tmp;
        }
        return cur;
    }
}
```

## 翻转链表类

### [206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)

> ```
> 输入: 1->2->3->4->5->NULL
> 输出: 5->4->3->2->1->NULL
> ```

````java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverseList(ListNode head) {
        ListNode cur = head, prev = null;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
}
````

### [92. 反转链表 II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> ```
> 输入：head = [1,2,3,4,5], left = 2, right = 4
> 输出：[1,4,3,2,5]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg)

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverseBetween(ListNode head, int left, int right) {
        ListNode dummy = new ListNode(-1);
        dummy.next = head;
        ListNode a = dummy;
        for (int i = 0; i < left - 1; ++i) a = a.next;
        ListNode b = a.next, c = b.next;
        int k = right - left;
        while (k-- > 0) {
            ListNode t = c.next;
            c.next = b;
            b = c;
            c = t;
        }
        a.next.next = c;
        a.next = b;
        return dummy.next;
    }
}
```

### [剑指 Offer 06. 从尾到头打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

> ```
> 输入：head = [1,3,2]
> 输出：[2,3,1]
> ```

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public int[] reversePrint(ListNode head) {
        if (head == null) return new int[]{};
        ListNode dummy = new ListNode(-1);
        dummy.next = head;
        ListNode a = dummy;
        ListNode b = a.next, c = b.next;
        while (c != null && b != null) {
            ListNode t = c.next;
            c.next = b;
            b = c;
            c = t; 
        }  
        a.next.next = c;
        a.next = b; 
        List<Integer> ans = new ArrayList<>();
        for (ListNode p = dummy.next; p != null; p = p.next) {
            ans.add(p.val);
        }
        return ans.stream().mapToInt(Integer::valueOf).toArray();
    }
}
```

### [143. 重排链表](https://leetcode-cn.com/problems/reorder-list/)

> ```
> 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
> ```

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public void reorderList(ListNode head) {
        if (head == null) return;
        int n = 0;
        for (ListNode p = head; p != null; p = p.next) n++;
        ListNode mid = head;
        for (int i = 0; i < (n + 1) / 2 - 1; ++i) mid = mid.next;
        ListNode a = mid, b = a.next;
        for (int i = 0; i < n / 2; ++i) {
            ListNode c = b.next;
            b.next = a;
            a = b;
            b = c;
        }
        ListNode p = head, q = a;
        for (int i = 0; i < n / 2; ++i) {
            ListNode o = q.next;
            q.next = p.next;
            p.next = q;
            p = q.next;
            q = o;
        }
        if (n % 2 == 1) mid.next = null;
        else mid.next.next = null;
    }
}
```

### [25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

> ```
> 输入：head = [1,2,3,4,5], k = 2
> 输出：[2,1,4,3,5]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex1.jpg)

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(-1);
        dummy.next = head;
        ListNode p = dummy;
        while (p != null) {
            ListNode q = p;
            for (int i = 0; i < k && q != null; ++i) q = q.next;
            if (q == null) break;
            ListNode a = p.next, b = a.next;
            for (int i = 0; i < k - 1; ++i) {
                ListNode c = b.next;
                b.next = a;
                a = b;
                b = c;
            }
            ListNode t = p.next;
            p.next = a;
            t.next = b;
            p = t;
        }
        return dummy.next;
    }
}
```

### [234. 回文链表](https://leetcode-cn.com/problems/palindrome-linked-list/)

> ```
> 输入: 1->2->2->1
> 输出: true
> ```

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public boolean isPalindrome(ListNode head) {
        int n = 0;
        for (ListNode p = head; p != null; p = p.next) n++;
        if (n == 1) return true;
        ListNode a = head;
        for (int i = 0; i < (n + 1) / 2; ++i) a = a.next;
        ListNode b = a.next;
        for (int i = 0; i < n / 2 - 1; ++i) {
            ListNode c = b.next;
            b.next = a;
            a = b;
            b = c;
        }
        ListNode p = head, q = a;
        for (int i = 0; i < n / 2; ++i) {
            if (p.val != q.val) return false;
            p = p.next;
            q = q.next;
        }
        return true;
    }
}
```

## 相交链表类

### [160. 相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

> ```
> 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
> 输出：Reference of the node with value = 8
> 输入解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
> ```
>
> ![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_example_1.png)

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        ListNode A  = headA, B = headB;
        while (A != B) {
            A = A == null ? headB : A.next;
            B = B == null ? headA : B.next;
        }
        return A;
    }
}
```

### [141. 环形链表](https://leetcode-cn.com/problems/linked-list-cycle/)

> ```
> 输入：head = [3,2,0,-4], pos = 1
> 输出：true
> 解释：链表中有一个环，其尾部连接到第二个节点。
> ```
>
> ![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist.png)

```java
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public boolean hasCycle(ListNode head) {
        if (head == null) return false;
        ListNode slow = head, fast = head.next;
        while (slow != fast) {
            if (fast == null || fast.next == null) return false;
            slow = slow.next;
            fast = fast.next.next;
        }
        return true;
    }
}
```











