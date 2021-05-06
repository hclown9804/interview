# CodeTop

### [3. 无重复字符的最长子串(mid)](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/) 

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

### [718. 最长重复子数组(mid)](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/)

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

### [110. 平衡二叉树(easy)](https://leetcode-cn.com/problems/balanced-binary-tree/)

> ```
> 输入：root = [3,9,20,null,null,15,7]
> 输出：true
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/10/06/balance_1.jpg)

####  思路一：自顶向下递归

计算每个节点左子树和右子树的高度，判断高度差是否超过1，同时递归判断左右子树是否为平衡树。

时间复杂度：$O(NlogN)$，$isBalanced$ 遍历所有节点，占用 $O(N)$ ；$depth$ 遍历子树的所有节点，占用 $O(logN)$ 。

```java
class Solution {
    public int depth(TreeNode root) {
        if (root == null) return 0;
        return Math.max(depth(root.left), depth(root.right)) + 1;
    }

    public boolean isBalanced(TreeNode root) {
        if (root == null) return true;
        return isBalanced(root.left) && isBalanced(root.right) && Math.abs(depth(root.left) - depth(root.right)) <= 1;
    }
}
```

#### 思路二：自底向上递归

提前终止不符合的情况，直接返回。

时间复杂度：$O(N)$

```java
class Solution {
    public boolean isBalanced(TreeNode root) {
        return dfs(root) != -1;
    }

    public int dfs(TreeNode root) {
        if (root == null) return 0;
        int left = dfs(root.left);
        if (left == -1) return -1;
        int right = dfs(root.right);
        if (right == -1) return -1;
        return Math.abs(left - right) < 2 ? Math.max(left, right) + 1 : -1; 
    }
}
```

### [124. 二叉树中的最大路径和(hard)](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

> ```
> 输入：root = [-10,9,20,null,null,15,7]
> 输出：42
> 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg)

#### 思路：DFS

1.使用全局变量 $ans$ 记录结果；

2.计算单个节点的路径和，递归计算左右子树的路径和，如果小于 $0$ 则看作 $0$ ；

3.更新当前的 $ans$ 结果，与左右子树路径和与当前节点值之和；

4.返回子树的路径和，即左右子树路径和的较大值与当前节点值之和。

时间复杂度：$O(N)$

```java
class Solution {
    int ans = Integer.MIN_VALUE;
    public int maxPathSum(TreeNode root) {
        if (root == null) return 0;
        dfs(root);
        return ans;
    }

    public int dfs(TreeNode root) {
        if (root == null) return 0;
        int left = Math.max(0, dfs(root.left));
        int right = Math.max(0, dfs(root.right));
        ans = Math.max(ans, root.val + left + right);
        return root.val + Math.max(left, right);
    }
}
```

### [155. 最小栈(easy)](https://leetcode-cn.com/problems/min-stack/)

> ```
> 输入：
> ["MinStack","push","push","push","getMin","pop","top","getMin"]
> [[],[-2],[0],[-3],[],[],[],[]]
> 
> 输出：
> [null,null,null,null,-3,null,0,-2]
> 
> 解释：
> MinStack minStack = new MinStack();
> minStack.push(-2);
> minStack.push(0);
> minStack.push(-3);
> minStack.getMin();   --> 返回 -3.
> minStack.pop();
> minStack.top();      --> 返回 0.
> minStack.getMin();   --> 返回 -2.
> ```

#### 思路一：辅助栈

使用一个辅助栈来保存最小值。

```java
class MinStack {
    Stack<Integer> stk1, stk2;
    /** initialize your data structure here. */
    public MinStack() {
        stk1 = new Stack<>();
        stk2 = new Stack<>();
        stk2.push(Integer.MAX_VALUE);
    }
    
    public void push(int val) {
        stk1.push(val);
        stk2.push(Math.min(stk2.peek(), val));
    }
    
    public void pop() {
        stk1.pop();
        stk2.pop();
    }
    
    public int top() {
        return stk1.peek();
    }
    
    public int getMin() {
        return stk2.peek();
    }   
}
```

#### 思路二：元组思想

使用一个二元组来保存当前值和最小值。

```java
class MinStack {
    Stack<int[]> stk = new Stack<>();
    /** initialize your data structure here. */
    public MinStack() {

    }
    
    public void push(int val) {
        if (stk.isEmpty()) stk.push(new int[]{val,val});
        else stk.push(new int[]{val, Math.min(val, stk.peek()[1])});
    }
    
    public void pop() {
        stk.pop();
    }
    
    public int top() {
        return stk.peek()[0];
    }
    
    public int getMin() {
        return stk.peek()[1];
    }
}
```

#### 思路三：链表

使用链表代替栈存储。

```java
class MinStack {
    class Node {
        int val, min;
        Node next;
        public Node(int val, int min) {
            this.val = val;
            this.min = min;
            next = null;
        }
    }
    Node head;
    /** initialize your data structure here. */
    public MinStack() {

    }
    
    public void push(int val) {
        if (head == null) head = new Node(val, val);
        else {
            Node cur = new Node(val, Math.min(val, head.min));
            cur.next = head;
            head = cur;
        }
    }
    
    public void pop() {
        if (head != null) head = head.next;
    }
    
    public int top() {
        if (head != null) return head.val;
        return -1;
    }
    
    public int getMin() {
        if (head != null) return head.min;
        return -1;
    }
}
```

### [144. 二叉树的前序遍历(mid)](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)

> ```
> 输入：root = [1,null,2,3]
> 输出：[1,2,3]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/09/15/inorder_1.jpg)

#### 思路一：递归

先访问根节点再递归遍历左右子树。

时间复杂度：$O(N)$

```java
class Solution {
    List<Integer> ans = new ArrayList<>();

    public void dfs(TreeNode root) {
        if (root == null) return;
        ans.add(root.val);
        dfs(root.left);
        dfs(root.right);
    }

    public List<Integer> preorderTraversal(TreeNode root) {
        if (root == null) return ans;
        dfs(root);
        return ans;
    }
}
```

#### 思路二：非递归

维护一个栈来存储左子树节点。

时间复杂度：$O(N)$

```java
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Stack<TreeNode> stk = new Stack<>();
        while (!stk.isEmpty() || root != null) {
            while (root != null) {
                stk.push(root);
                ans.add(root.val);
                root = root.left;
            }
            root = stk.pop();
            root = root.right;
        }
        return ans;
    }
}
```

### [105. 从前序与中序遍历序列构造二叉树(mid)](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

> ```
> 输入：
>     前序遍历 preorder = [3,9,20,15,7]
>     中序遍历 inorder = [9,3,15,20,7]
> 输出：[3,9,20,null,null,15,7]
> 
>     3
>    / \
>   9  20
>     /  \
>    15   7
> ```

#### 思路：递归

1.使用 $HashMap$ 存储 $inorder$ 中序遍历的节点值以及对应下标；

2.递归重建二叉树：

* $pl$ ：子树前序遍历的左端点，$pr$：子树前序遍历的右端点；
* $il$ ：子树中序遍历的左端点，$ir$：子树中序遍历的右端点；

* 获取当前子树的根节点，即 $preorder$ 前序遍历的第一个节点 $pl$ ;
* 获取根节点对应中序遍历的下标 $k$；
* 递归重建根节点的左右子树：
  * 左子树：前序遍历：$[pl+1,pl+k-il]$；中序遍历：$[il,k-1]$
  * 计算左子树的节点个数：$k-il-1$
  * 右子树：前序遍历：$[pl+k-il+1,pr]$；中序遍历：$[k+1,ir]$

* 返回根节点。

时间复杂度：$O(N)$

```java
class Solution {
    HashMap<Integer, Integer> map = new HashMap<>();
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        for (int i = 0; i < inorder.length; ++i) map.put(inorder[i], i);
        return build(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    public TreeNode build(int[] preorder, int pl, int pr, int[] inorder, int il, int ir) {
        if (pl > pr) return null;
        TreeNode root = new TreeNode(preorder[pl]);
        int k = map.get(preorder[pl]);
        root.left = build(preorder, pl + 1, pl + k - il, inorder, il, k - 1);
        root.right = build(preorder, pl + k - il + 1, pr, inorder, k + 1, ir);
        return root;
    }
}
```









