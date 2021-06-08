# CodeTop

### [206. 反转链表（easy)](https://leetcode-cn.com/problems/reverse-linked-list/)

> ```
> 输入：head = [1,2,3,4,5]
> 输出：[5,4,3,2,1]
> ```

```java
class Solution {
    public ListNode reverseList(ListNode head) {
        ListNode prev = null, cur = head;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
}
```

### [215. 数组中的第K个最大元素(mid)](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

> ```
> 输入: [3,2,1,5,6,4] 和 k = 2
> 输出: 5
> ```

#### 思路一：快速排序

* 使用快速排序的 $partition$ 过程，对于这样的一次过程，可以确定一个元素 $x$ 的最终位置，即它前面的每个元素都大于它，后面的每个元素都小于等于它。
* 在每次划分数组之后，判断 $pivot$ 在划分后的位置；
* 如果位置正好为 $k$ ，则直接返回 $pivot$ ；
* 否则判断是应该在左边还是右边继续进行搜索。

时间复杂度：$O(N)$

```java
class Solution {
    public int findKthLargest(int[] nums, int k) {
        return quick_select(nums, 0, nums.length - 1, k - 1);
    }

    public int quick_select(int[] nums, int l, int r, int k) {
        if (l == r) return nums[k];
        int x = nums[l + r >> 1], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (nums[i] > x);
            do j--; while (nums[j] < x);
            if (i < j) swap(nums, i, j);
        }
        if (k <= j) return quick_select(nums, l, j, k);
        else return quick_select(nums, j + 1, r, k);
    }

    public void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
```

#### 思路二：堆排序

建立大根堆，做 $k-1$ 次删除操作堆顶元素即为答案。

时间复杂度：$O(NlogN)$

```java
class Solution {
    public int findKthLargest(int[] nums, int k) {
        int size = nums.length - 1;
        for (int i = size / 2; i >= 0; --i) down(nums, i, nums.length);
        for (int i = nums.length - 1; i >= nums.length - k + 1; --i) {
            swap(nums, 0, i);
            size--;
            down(nums, 0, size);
        }
        return nums[0];
    }

    public void down(int[] h, int u, int size) {
        int t = u;
        if (u * 2 + 1 < size && h[u * 2 + 1] > h[t]) t = u * 2 + 1;
        if (u * 2 + 2 < size && h[u * 2 + 2] > h[t]) t = u * 2 + 2;
        if (u != t) {
            swap(h, u, t);
            down(h, t, size);
        }
    }

    public void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
```

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

### [25. K 个一组翻转链表(hard)](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

> ```
> 输入：head = [1,2,3,4,5], k = 3
> 输出：[3,2,1,4,5]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/10/03/reverse_ex2.jpg)

#### 代码

```java
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

### [113. 路径总和 II(mid)](https://leetcode-cn.com/problems/path-sum-ii/)

> ```
> 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
> 输出：[[5,4,11,2],[5,8,4,5]]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/01/18/pathsumii1.jpg)

#### 思路一：DFS

1.对二叉树进行 $DFS$ ，计算每一个节点到叶节点的路径值；使用列表 $ans$ 存储所有解，列表$path$  记录当前解；

2.在遍历到当前节点时，$targetSum$ 减去当前节点的值，若此时节点为叶节点且 $targetSum$ 刚好为 $0$ 时，将当前解 $path$ 添加到解集中；

3.递归遍历左右子树；

4.删去 $path$ 中的最后一个节点，即删除当前子树的根节点，回复现场。

时间复杂度：$O(N^2)$

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public void dfs(TreeNode root, int targetSum) {
        if (root == null) return;
        targetSum -= root.val;
        path.add(root.val);
        if (targetSum == 0 && root.left == null && root.right == null)
            ans.add(new ArrayList<>(path));
        dfs(root.left, targetSum);
        dfs(root.right, targetSum);
        path.remove(path.size() - 1);
    }

    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        dfs(root, targetSum);
        return ans;
    }
}
```

#### 思路二：BFS

1.首先定义一个对象 $Node$，用来存储当前节点以及到当前节点的路径和（不含当前节点），使用一个 $HashMap$ 来存储当前节点以及它的父节点；

2.对二叉树进行 $BFS$：

* 队列存储 $Node$ 对象，根节点入队；

* 当队列非空时，队列出队，计算当前节点路径和，如果当前节点为叶节点且路径和等于 $targetSum$，从当前节点根据 $HashMap$ 存储结果向上追溯从而找到路径，加入解集，由于是自底向上回溯，需要将解翻转；
* 若当前节点不是叶节点，则将非空子节点加入 $HashMap$ 并且入队。

时间复杂度：$O(N^2)$

```java
class Solution {       
    class Node {
        TreeNode node;
        int val;
        public Node(TreeNode node, int val) {
            this.node = node;
            this.val = val;
        }
    }
    
    List<List<Integer>> ans = new ArrayList<>();
    HashMap<TreeNode, TreeNode> map = new HashMap<>();    
    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        if (root == null) return ans;
        Queue<Node> queue = new LinkedList<>();
        queue.offer(new Node(root, 0));

        while (!queue.isEmpty()) {
            Node node = queue.poll();
            TreeNode cur = node.node;
            int t = node.val + cur.val;
            if (cur.left == null && cur.right == null) {
                if (t == targetSum) getPath(cur);
            } else {
                if (cur.left != null) {
                    map.put(cur.left, cur);
                    queue.offer(new Node(cur.left, t));
                }
                if (cur.right != null) {
                    map.put(cur.right, cur);
                    queue.offer(new Node(cur.right, t));
                }
            }
        }
        return ans;
    }

    public void getPath(TreeNode root) {
        ArrayList<Integer> path = new ArrayList<>();
        while (root != null) {
            path.add(root.val);
            root = map.get(root);
        }
        Collections.reverse(path);
        ans.add(new ArrayList<Integer>(path));
    }
}
```

### [234. 回文链表(easy)](https://leetcode-cn.com/problems/palindrome-linked-list/)

> ```
> 输入: 1->2->2->1
> 输出: true
> ```

#### 思路：反转链表

虽然本题原难度是 $easy$ ，但是加上时空复杂度限制之和可以算一道 $mid$ 题了。

1.首先找出链表的中点，从中点开始对后半部分进行反转；

2.使用两个指针，一个从头开始，一个从尾开始，因为已经反转，两个指针同时遍历，一旦有一个值不相等，则不是回文链表。

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```java
// 根据长度计算中点
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

// 快慢指针求中点
class Solution {
    public boolean isPalindrome(ListNode head) {
        ListNode mid = getMid(head);
        ListNode p = head, s = mid.next;
        mid.next = null;
        ListNode q = reverse(s);
        while (p != null && q != null) {
            if (p.val != q.val) return false;
            p = p.next;
            q = q.next;
        }
        return true;
    }

    public ListNode getMid(ListNode head) {
        ListNode s = head, f = head.next;
        while (f != null && f.next != null) {
            s = s.next;
            f = f.next.next;
        }
        return s;
    }

    public ListNode reverse(ListNode head) {
        ListNode prev = null, cur = head;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
}
```

### [146. LRU 缓存机制(mid)](https://leetcode-cn.com/problems/lru-cache/)

> ```
> 输入
> ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
> [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
> 输出
> [null, null, null, 1, null, -1, null, -1, 3, 4]
> 
> 解释
> LRUCache lRUCache = new LRUCache(2);
> lRUCache.put(1, 1); // 缓存是 {1=1}
> lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
> lRUCache.get(1);    // 返回 1
> lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
> lRUCache.get(2);    // 返回 -1 (未找到)
> lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
> lRUCache.get(1);    // 返回 -1 (未找到)
> lRUCache.get(3);    // 返回 3
> lRUCache.get(4);    // 返回 4
> ```

#### 思路：哈希表+双向链表

* 使用哈希表+双向链表维护所有在缓存中的数据；
* 按顺序存储数据，头部为最近使用的，尾部为最久未使用的。

```java
class LRUCache {
    class Node {
        int key, value;
        Node left, right;
        public Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    HashMap<Integer, Node> map = new HashMap<>();
    Node L, R;
    int n;

    public LRUCache(int capacity) {
        n = capacity;
        L = new Node(-1, -1);
        R = new Node(-1, -1);
        L.right = R;
        R.left = L;
    }
    
    public int get(int key) {
        if (!map.containsKey(key)) return -1;
        Node p = map.get(key);
        remove(p);
        insert(p);
        return p.value;
    }
    
    public void put(int key, int value) {
        if (map.containsKey(key)) {
            Node p = map.get(key);
            p.value = value;
            remove(p);
            insert(p);
        } else {
            if (n == map.size()) {
                Node p = R.left;
                remove(p);
                map.remove(p.key);
            }
            Node p = new Node(key, value);
            insert(p);
            map.put(key, p);
        }
    }

    public void remove(Node p) {
        p.left.right = p.right;
        p.right.left = p.left;
    }

    public void insert(Node p) {
        p.left = L;
        p.right = L.right;
        L.right.left = p;
        L.right = p;
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
```

### [42. 接雨水(hard)](https://leetcode-cn.com/problems/trapping-rain-water/)

> ```
> 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
> 输出：6
> 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
> ```
>
> ![](https://i.loli.net/2021/05/31/zCR8uild3KrZIJG.png)

#### 思路：单调栈

* 记录每个位置左边和右边第一个比自身不低的矩形条，对三个矩形条围成的 $U$ 型按照行进行分解计算面积；
* 维护一个单调递减的单调栈，每次元素出栈时，$i$ 为右边第一个比 $stk.peek()$ 不低的矩形，$stk.pop()$ 弹出栈顶，并记录为 $top$，假设此时栈中仍有元素，此时新的栈顶 $stk.peek()$ 、$top$、$i$ 构成一个 $U$ 型，其中 $top$ 代表底部，计算宽度为 $i - stk.peek() - 1$ ，高度为左右矩形较低值与 $top$ 的差值即为 $Math.min(height[stk.peek()], height[i]) - height[top]$。

时间复杂度：$O(N)$

空间复杂度：$O(N)$

```java
class Solution {
    public int trap(int[] height) {
        int n = height.length, ans = 0;
        Deque<Integer> stk = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            while (!stk.isEmpty() && height[stk.peek()] <= height[i]) {
                int top = stk.pop();
                if (stk.isEmpty()) break;
                ans += (i - stk.peek() - 1) * (Math.min(height[stk.peek()], height[i]) - height[top]);
            }
            stk.push(i);
        }
        return ans;
    }
}
```

### [33. 搜索旋转排序数组(mid)](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)

> ```
> 输入：nums = [4,5,6,7,0,1,2], target = 0
> 输出：4
> ```

#### 思路：二分

* 第一次二分找到大于等于 $nums[0]$ 的右边界；
* 若 $nums[0]$ 小于等于 $target$  ，则 $target$ 在左边，否则更新边界；
* 第二次二分找到大于等于 $target$ 的左边界，若二分的边界值不等于 $target$，则查找失败。

时间复杂度：$O(logN)$

空间复杂度：$O(1)$

```java
class Solution {
    public int search(int[] nums, int target) {
        int n = nums.length;
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if (nums[mid] >= nums[0]) l = mid;
            else r = mid - 1;
        } 
        if (nums[0] <= target) l = 0;
        else {
            l = r + 1;
            r = n - 1;
        }
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= target) r = mid;
            else l = mid + 1;
        }
        if (nums[r] == target) return r;
        return -1;
    }
}
```

### [31. 下一个排列(mid)](https://leetcode-cn.com/problems/next-permutation/)

> ```
> 输入：nums = [1,2,3]
> 输出：[1,3,2]
> 
> 输入：nums = [3,2,1]
> 输出：[1,2,3]
> ```

#### 思路

* 从后往前寻找第一个相邻升序的元素对 $(i, j)$，满足 $nums[i] < nums[j]$，则 $j$ 后面元素为降序排列；
* 在 $j$ 后面从后往前寻找第一个满足 $nums[i] < nums[k]$ 的元素；
* 交换 $nums[i]$ 和$nums[k]$；
* 将 $j$ 后面所有元素逆序，即转换为升序排列。

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```java
class Solution {
    public void nextPermutation(int[] nums) {
        int n = nums.length;
        if (n <= 1) return;
        int i = n - 2, j = n - 1, k = n - 1;
        while (i >= 0 && nums[i] >= nums[j]) {
            i--;
            j--;
        }
        if (i >= 0) {
            while (nums[i] >= nums[k]) k--;
            swap(nums, i, k);
        }
        reverse(nums, j, n - 1);
    }
        
    private void reverse(int[] nums, int i, int j){
        while(i < j) swap(nums, i++, j--);
    }

    public void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
```

### [23. 合并K个升序链表(hard)](https://leetcode-cn.com/problems/merge-k-sorted-lists/)

> ```
> 输入：lists = [[1,4,5],[1,3,4],[2,6]]
> 输出：[1,1,2,3,4,4,5,6]
> 解释：链表数组如下：
> [
>   1->4->5,
>   1->3->4,
>   2->6
> ]
> 将它们合并到一个有序链表中得到。
> 1->1->2->3->4->4->5->6
> ```

####  思路：归并

使用归并排序思路进行排序

时间复杂度：$O(kN*logk)$

空间复杂度：$O(logk)$

```java
class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        return merge(lists, 0, lists.length - 1);
    }

    public ListNode merge(ListNode[] lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return null;
        int mid = l + r >> 1;
        return mergeTwoList(merge(lists, l, mid), merge(lists, mid + 1 , r));
    }

    public ListNode mergeTwoList(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null) return l1 == null ? l2 : l1;
        ListNode dummy = new ListNode(-1), cur = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) {
                cur.next = l1;               
                l1 = l1.next;
            } else {
                cur.next = l2;
                l2 = l2.next;
            }
            cur = cur.next;
        }
        if (l1 == null) cur.next = l2;
        if (l2 == null) cur.next = l1;
        return dummy.next;
    }
}
```

### [199. 二叉树的右视图(mid)](https://leetcode-cn.com/problems/binary-tree-right-side-view/)

> ```
> 输入: [1,2,3,null,5,null,4]
> 输出: [1, 3, 4]
> 解释:
> 
>    1            <---
>  /   \
> 2     3         <---
>  \     \
>   5     4       <---
> ```

#### 思路：层序遍历

时间复杂度：$O(N)$

空间复杂度：$O(N)$

```java
class Solution {
    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size-- > 0) {
                TreeNode t = queue.poll();
                if (t.left != null) queue.offer(t.left);
                if (t.right != null) queue.offer(t.right);
                if (size == 0) ans.add(t.val);
            }
        }
        return ans;
    }
}
```

### [54. 螺旋矩阵(mid)](https://leetcode-cn.com/problems/spiral-matrix/)

> ```
> 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
> 输出：[1,2,3,6,9,8,7,4,5]
> ```
>
> ![](https://i.loli.net/2021/06/01/uDhyxcPrlNnwVS8.png)

#### 思路

* 使用方向数组控制当元素遍历到边界时的情况；
* 使用 $boolean$ 数组记录当前数字是否遍历过；

时间复杂度：$O(NM)$

空间复杂度：$O(NM)$

```java
class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> ans = new ArrayList<>();
        int n = matrix.length;
        if (n == 0) return ans;
        int m = matrix[0].length;
        int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        boolean[][] st = new boolean[n][m];
        for (int i = 0, d = 0, x = 0, y = 0; i < n * m; ++i) {
            st[x][y] = true;
            ans.add(matrix[x][y]);
            int a = x + dx[d], b = y + dy[d];
            if (a < 0 || a >= n || b < 0 || b >= m || st[a][b]) {
                d = (d + 1) % 4;
                a = x + dx[d];
                b = y + dy[d];
            }
            x = a; y = b;
        }
        return ans;
    }
}
```

### [143. 重排链表(mid)](https://leetcode-cn.com/problems/reorder-list/)

> ```
> 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
> ```

#### 思路

* 找出链表的中间节点，断开中间节点，从中间节点开始翻转链表；
* 两个指针，一个从链表头开始，一个从链表尾开始，遍历直到中间节点，依次连接；

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```java
class Solution {
    public void reorderList(ListNode head) {
        if (head == null) return;
        ListNode mid = getMid(head); 
        ListNode p = head, q = mid.next;
        mid.next = null;
        q = reverseList(q);
        merge(p, q);
    }

    public ListNode getMid(ListNode head) {
        ListNode s = head, f = head.next;
        while (f != null && f.next != null) {
            s = s.next;
            f = f.next.next;
        }
        return s;
    }

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

    public void merge(ListNode l1, ListNode l2) {
        ListNode cur1, cur2;
        while (l1 != null && l2 != null) {
            cur1 = l1.next;
            cur2 = l2.next;
            l1.next = l2;
            l1 = cur1;
            l2.next = l1;
            l2 = cur2;
        }
    }
}
```

### [300. 最长递增子序列(mid)](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

> ```
> 输入：nums = [10,9,2,5,3,7,101,18]
> 输出：4
> 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
> ```

#### 思路：DP

时间复杂度：$O(N^2)$

空间复杂度：$O(N)$

```java
class Solution {
    public int lengthOfLIS(int[] nums) {
        int n = nums.length, ans = 1;
        if (n == 0) return 0;
        int[] f = new int[n];
        f[0] = 1;
        for (int i = 1; i < n; ++i) {
            f[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) f[i] = Math.max(f[i], f[j] + 1);
            }
            ans = Math.max(ans, f[i]);
        }
        return ans;
    }
}
```

### [92. 反转链表 II(mid)](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> ```
> 输入：head = [1,2,3,4,5], left = 2, right = 4
> 输出：[1,4,3,2,5]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/02/19/rev2ex2.jpg)

```java
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

### [124. 二叉树中的最大路径和(hard)](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

> ```
> 输入：root = [1,2,3]
> 输出：6
> 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
> ```

#### 思路：搜索

* 记录全局变量 $ans$；
* 分别递归计算左右子树大于0的值；
* 累加左右节点值与根节点值更新 $ans$；

时间复杂度：$O(N)$

空间复杂度：$O(N)$

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
        int left = 0, right = 0;
        if (root.left != null) left = Math.max(left, dfs(root.left));
        if (root.right != null) right = Math.max(right, dfs(root.right));
        ans = Math.max(ans, left + right + root.val);
        return Math.max(left, right) + root.val;
    }
}
```

### [200. 岛屿数量(mid)](https://leetcode-cn.com/problems/number-of-islands/)

> ```
> 输入：grid = [
>   ["1","1","1","1","0"],
>   ["1","1","0","1","0"],
>   ["1","1","0","0","0"],
>   ["0","0","0","0","0"]
> ]
> 输出：1
> ```

#### 思路1：DFS

时间复杂度：$O(N*M)$

空间复杂度：$O(N*M)$

```java
class Solution {
    int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
    public void dfs(char[][] grid, int x, int y) {
        grid[x][y] = '#';
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= grid.length || b < 0 || b >= grid[0].length || grid[a][b] != '1') continue;
            dfs(grid, a, b);
        }
    }

    public int numIslands(char[][] grid) {
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1') {
                    ans++;
                    dfs(grid, i, j);
                }
            }
        }
        return ans;
    }
}
```

#### 思路2：BFS

时间复杂度：$O(N*M)$

空间复杂度：$O(min(N, M))$

```java
class Solution {
    public int numIslands(char[][] grid) {
        int n = grid.length;
        if (n == 0) return 0;
        int m = grid[0].length;
        int ans = 0;
        int[] dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1') {
                    ++ans;
                    grid[i][j] = '#';
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    while (!queue.isEmpty()) {
                        int[] t = queue.poll();
                        int x = t[0], y = t[1];
                        for (int k = 0; k < 4; ++k) {
                            int a = x + dx[k], b = y + dy[k];
                            if (a < 0 || a >= n || b < 0 || b >= m || grid[a][b] != '1') continue;
                            grid[a][b] = '#';
                            queue.offer(new int[]{a, b});
                        }
                    }
                }
            }
        }
        return ans;
    }
}
```

### 排序奇升偶降链表

> ```
> 给定链表 1->8->3->6->5->4->7->2, 重新排列为 1->2->3->4->5->6->7->8.
> 奇数位置按序增长，偶数位置按序递减，如何能实现链表从小到大？
> ```

#### 思路

* 分离奇数位置和偶数位置的两个链表；
* 对偶数位置链表进行反转；
* 合并两边链表为有序链表。

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```java
public class Main {
    static class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) {
            this.val = val;
        }
        ListNode(int val, ListNode next) {
            this.val = val;
            this.next = next;
        }
    }

    public static void main(String[] args) {
        ListNode head = new ListNode(1);
        ListNode p = head;

        int[] nums = new int[]{8, 3, 6, 5, 4, 7, 2};
        for (int i = 0; i < nums.length; ++i) {
            p.next = new ListNode(nums[i]);
            p = p.next;
        }
        print(head);

        ListNode[] ps = partition(head);
        ListNode p1 = ps[0], p2 = ps[1];
        p2 = reverse(p2);

        print(p1);
        print(p2);

        ListNode ans = merge(p1, p2);
        print(ans);
    }

    public static void print(ListNode p) {
        while (p.next != null) {
            System.out.print(p.val + "->");
            p = p.next;
        }
        System.out.print(p.val);
        System.out.println();
    }

    public static ListNode[] partition(ListNode head) {
        ListNode p2 = head.next;
        ListNode cur1 = head, cur2 = p2;
        while (cur2 != null && cur2.next != null) {
            cur1.next = cur2.next;
            cur1 = cur1.next;
            cur2.next = cur1.next;
            cur2 = cur2.next;
        }
        cur1.next = null;
        return new ListNode[]{head, p2};
    }

    public static ListNode reverse(ListNode head) {
        ListNode prev = null, cur = head;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    public static ListNode merge(ListNode p1, ListNode p2) {
        if (p1 == null || p2 == null) return p1 == null ? p2 : p1;
        ListNode dummy = new ListNode(-1);
        ListNode p = dummy;
        while (p1 != null && p2 != null) {
            if (p1.val <= p2.val) {
                p.next = p1;
                p1 = p1.next;
            } else {
                p.next = p2;
                p2 = p2.next;
            }
            p = p.next;
        }
        if (p1 == null) p.next = p2;
        if (p2 == null) p.next = p1;
        return dummy.next;
    }
}
```

### [41. 缺失的第一个正数(hard)](https://leetcode-cn.com/problems/first-missing-positive/)

> ```
> 输入：nums = [1,2,0]
> 输出：3
> 
> 输入：nums = [3,4,-1,1]
> 输出：2
> 
> 输入：nums = [7,8,9,11,12]
> 输出：1
> ```

#### 思路

* 如果数组不缺失数字的话，按照从小到大则应该是  $1$ 到 $n$ 放在数组中；
* 遍历数组，将数字放到自己对应的位置，$1$ 放到下标为 $0$ 的地方，依此类推；
* 如果数字已经放在对应位置则跳出循环。

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```java
class Solution {
    public int firstMissingPositive(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) swap(nums, nums[i] - 1, i);
        }
        for (int i = 0; i < n; ++i) System.out.println(nums[i]);
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }

    public void swap(int[] nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
}
```

### [46. 全排列(mid)](https://leetcode-cn.com/problems/permutations/)

> ```
> 输入：nums = [1,2,3]
> 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
> ```

#### 思路：回溯

时间复杂度：$O(N*N!)$

空间复杂度：$O(N)$

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();
    boolean[] st;

    public void dfs(int[] nums, int u) {
        int n = nums.length;
        if (u == n) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!st[i]) {
                path.add(nums[i]);
                st[i] = true;
                dfs(nums, u + 1);
                st[i] = false;
                path.remove(path.size() - 1);
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

### [56. 合并区间(mid)](https://leetcode-cn.com/problems/merge-intervals/)

> ```
> 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
> 输出：[[1,6],[8,10],[15,18]]
> 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
> ```

#### 思路：排序

* 对数组中的元素按照左端点排序；
* 将数组中的集合入队，如果当前集合元素的左端点小于等于队列尾集合的右端点值，则更新队列尾集合的右端点，否则将当前集合入队。

时间复杂度：$O(NlogN)$

空间复杂度：$O(logN)$

```java
class Solution {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, (a, b)->(a[0] - b[0]));
        Deque<int[]> queue = new LinkedList<>();
        for (int[] interval: intervals) {
            if (!queue.isEmpty() && interval[0] <= queue.peekLast()[1]) queue.peekLast()[1] = Math.max(queue.peekLast()[1], interval[1]);
            else queue.addLast(interval);
        }
        return queue.toArray(new int[queue.size()][2]);
    }
}
```

### [39. 组合总和(mid)](https://leetcode-cn.com/problems/combination-sum/)

> ```
> 输入：candidates = [2,3,5], target = 8,
> 所求解集为：
> [
>   [2,2,2,2],
>   [2,3,3],
>   [3,5]
> ]
> ```

#### 思路：搜索

* 枚举每个数，每次 $target$ 减去当前数，若为 $0$ 则找到一组解，若枚举到最后一个数也没有退出则无解，枚举当前数还可以使用几次，继续搜索，最后恢复现场。

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public void dfs(int[] nums, int target, int u) {
        if (target == 0) {
            ans.add(new ArrayList<>(path));
            return;
        }
        if (u == nums.length) return;
        for (int i = 0; i * nums[u] <= target; ++i) {
            dfs(nums, target - i * nums[u], u + 1);
            path.add(nums[u]);
        }
        for (int i = 0; i * nums[u] <= target; ++i) path.remove(path.size() - 1);
    }

    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        dfs(candidates, target, 0);
        return ans;
    }
}
```

### [470. 用 Rand7() 实现 Rand10()(mid)](https://leetcode-cn.com/problems/implement-rand10-using-rand7/)

#### 思路

* 最少调用两次 $rand7()$， 则生成 $1-49$ 的数；
* 若生成的数字大于40则直接拒绝；
* 将 $1-40$ 的数字减去1，为 $0-39$，将其对10取模，则得到10组数，每组四个数。

期望：$1/40/49*2=49/20=2.45$

```java
class Solution extends SolBase {
    public int rand10() {
        int t = (rand7() - 1) * 7 + rand7();
        if (t > 40) return rand10();
        return (t - 1) % 10 + 1;
    }
}
```

### [76. 最小覆盖子串(hard)](https://leetcode-cn.com/problems/minimum-window-substring/)

> ```
> 输入：s = "ADOBECODEBANC", t = "ABC"
> 输出："BANC"
> ```

#### 思路：滑动窗口+哈希表

* 使用两个哈希表，$hs$ 维护 $[j,i]$ 区间各个字符出现了多少次， $ht$ 维护 $t$ 中每个字符出现多少次；
* 使用变量 $cnt$ 维护 $[j,i]$ 区间满足 $t$ 中字符串的元素的个数；
* 将当前元素 $s[i]$ 加入 $hs$ 中，若 $hs[s[i]]<=ht[s[i]]$ 则 $cnt$++，若 $hs$ 中当前元素个数大于 $ht$ 中个数，则移动 $j$ 的位置并且更新 $hs$ 中的值；
* 判断当前维护的区间是否满足要求，满足则更新答案。

时间复杂度：$O(N)$

空间复杂度：$O(M)$ M：表示字符集大小

```java
class Solution {
    public String minWindow(String s, String t) {
        int[] hs = new int[128], ht = new int[128];
        char[] str = s.toCharArray();
        for (char c: t.toCharArray()) ht[c]++;
        String ans = "";
        int cnt = 0, len = Integer.MAX_VALUE;
        for (int i = 0, j = 0; i < s.length(); ++i) {
            hs[str[i]]++;
            if (hs[str[i]] <= ht[str[i]]) cnt++;
            while (j < i && hs[str[j]] > ht[str[j]]) hs[str[j++]]--;
            if (cnt == t.length() && i - j + 1 < len) {
                len = i - j + 1;
                ans = s.substring(j, i + 1);
            }
        }
        return ans;
    }
}
```

### [98. 验证二叉搜索树(mid)](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> ```
> 输入:
>     5
>    / \
>   1   4
>      / \
>     3   6
> 输出: false
> 解释: 输入为: [5,1,4,null,null,3,6]。
>      根节点的值为 5 ，但是其右子节点值为 4 。
> ```

### 思路：中序遍历

* 二叉搜索树的中序遍历是升序的。

```java
class Solution {
    public boolean isValidBST(TreeNode root) {
        if (root == null) return true;
        Deque<TreeNode> stack = new LinkedList<>();
        long prev = Long.MIN_VALUE;
        while (!stack.isEmpty() || root != null) {
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            if (prev >= root.val) return false;
            prev = root.val;
            root = root.right;
        }
        return true;
    }
}
```

```java
class Solution {
    public boolean isValidBST(TreeNode root) {
        return inorder(root);
    }

    long prev = Long.MIN_VALUE;
    public boolean inorder(TreeNode root) {
        if (root == null) return true;
        boolean l = inorder(root.left);
        if (prev >= root.val) return false;
        prev = root.val;
        boolean r = inorder(root.right);
        return l && r;
    }
}
```

### 圆环回原点问题

> ```
> 圆环上有10个点，编号为0~9。从0点出发，每次可以逆时针和顺时针走一步，问走n步回到0点共有多少种走法。
> 输入: 2
> 输出: 2
> 解释：有2种方案。分别是0->1->0和0->9->0
> ```

#### 思路：DP

* $f[i][j]$：表示从原点走 $i$ 步到 $j$ 的方案数；
* $f[i][j]=f[i-1][(j-1+length)\%length]+f[i-1][(j+1)\%length]$

```java
public static int dp(int n) {
    int length = 10;
    int[][] f = new int[n + 1][length];
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < length; ++j) {
            f[i][j] = f[i - 1][(j - 1 + length) % length] + f[i - 1][(j + 1) % length];
        }
    }
    return f[n][0];
}
```

### [162. 寻找峰值(mid)](https://leetcode-cn.com/problems/find-peak-element/)

> ```
> 输入：nums = [1,2,1,3,5,6,4]
> 输出：1 或 5 
> 解释：你的函数可以返回索引 1，其峰值元素为 2；
>      或者返回索引 5， 其峰值元素为 6。
> ```

#### 思路：二分

* 判断序列左边第一个 $mid$ 大于 $mid$ 下一个元素的元素

时间复杂度：$O(logN)$

空间复杂度：$O(1)$

```java
class Solution {
    public int findPeakElement(int[] nums) {
        int l = 0, r = nums.length - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] > nums[mid + 1]) r = mid;
            else l = mid + 1;
        }
        return l;
    }
}
```

### [48. 旋转图像(mid)](https://leetcode-cn.com/problems/rotate-image/)

> ```
> 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
> 输出：[[7,4,1],[8,5,2],[9,6,3]]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/08/28/mat1.jpg)

#### 思路：原地旋转

* 首先对矩阵根据水平线上下翻转，然后根据主对角线翻转。

时间复杂度：$O(N^2)$

空间复杂度：$O(1)$

```java
class Solution {
    public void rotate(int[][] matrix) {
        int n = matrix.length, m = matrix[0].length;
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix, i, j, n - 1 - i, j);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(matrix, i, j, j, i);
            }
        }
    }

    public void swap(int[][] nums, int x1, int y1, int x2, int y2) {
        int t = nums[x1][y1];
        nums[x1][y1] = nums[x2][y2];
        nums[x2][y2] = t;
    }
}
```

### [322. 零钱兑换(mid)](https://leetcode-cn.com/problems/coin-change/)

> ```
> 输入：coins = [1, 2, 5], amount = 11
> 输出：3 
> 解释：11 = 5 + 5 + 1
> ```

#### 思路：完全背包

时间复杂度：$O(amount*N)$

空间复杂度：$O(N)$

```java
class Solution {
    public int coinChange(int[] coins, int amount) {
        int[] f = new int[amount + 1];
        Arrays.fill(f, amount + 1);
        f[0] = 0;
        for (int x: coins) {
            for (int i = x; i <= amount; ++i) {
                f[i] = Math.min(f[i], f[i - x] + 1);
            }
        }
        return f[amount] > amount ? -1 : f[amount];
    }
}
```

### [518. 零钱兑换 II(mid)](https://leetcode-cn.com/problems/coin-change-2/)

> ```
> 输入: amount = 5, coins = [1, 2, 5]
> 输出: 4
> 解释: 有四种方式可以凑成总金额:
> 5=5
> 5=2+2+1
> 5=2+1+1+1
> 5=1+1+1+1+1
> ```

#### 思路：完全背包

时间复杂度：$O(amount*N)$

空间复杂度：$O(N)$

```java
class Solution {
    public int change(int amount, int[] coins) {
        int[] f = new int[amount + 1];
        f[0] = 1;
        for (int x: coins) {
            for (int i = x; i <= amount; ++i) {
                f[i] += f[i - x];
            }
        }
        return f[amount];
    }
}
```

### [958. 二叉树的完全性检验(mid)](https://leetcode-cn.com/problems/check-completeness-of-a-binary-tree/)

> ```
> 输入：[1,2,3,4,5,6]
> 输出：true
> 解释：最后一层前的每一层都是满的（即，结点值为 {1} 和 {2,3} 的两层），且最后一层中的所有结点（{4,5,6}）都尽可能地向左。
> ```
>
> ![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/15/complete-binary-tree-1.png)

#### 思路：BFS

* 标记是否遇到空节点，若已遇到且后面有非空节点则不是完全二叉树。

时间复杂度：$O(N)$

空间复杂度：$O(N)$

```java
class Solution {
    public boolean isCompleteTree(TreeNode root) {
        if (root == null) return true;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        boolean flag = false;
        while (!queue.isEmpty()) {
            TreeNode t = queue.poll();
            if (t == null) {
                flag = true;
                continue;
            } else {
                if (flag) return false;
                queue.offer(t.left);
                queue.offer(t.right);
            }
        }
        return true;
    }
}
```

### [20. 有效的括号(easy)](https://leetcode-cn.com/problems/valid-parentheses/)

> ```
> 输入：s = "()[]{}"
> 输出：true
> ```

#### 思路：栈

* 遇到左括号，栈中压入对应的右括号，遇到右括号，则匹配栈顶元素，若栈为空或不匹配则返回 $false$，最后判断栈是否为空。

时间复杂度：$O(N)$

空间复杂度：$O(N)$

```java
class Solution {
    public boolean isValid(String s) {
        Deque<Character> stack = new LinkedList<>();
        for (char c: s.toCharArray()) {
            if (c == '(') stack.push(')');
            else if (c == '[') stack.push(']');
            else if (c == '{') stack.push('}');
            else if (stack.isEmpty() || c != stack.pop()) return false;
        }
        return stack.isEmpty();
    }
}
```

### [148. 排序链表(mid)](https://leetcode-cn.com/problems/sort-list/)

> ```
> 输入：head = [4,2,1,3]
> 输出：[1,2,3,4]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2020/09/14/sort_list_1.jpg)

#### 思路：归并排序

* 找到链表中点并断开，递归对两个子链表归并。

时间复杂度：$O(NlongN)$

空间复杂度：$O(logN)$

```java
class Solution {
    public ListNode sortList(ListNode head) {
        if (head == null || head.next == null) return head;
        ListNode mid = getMid(head);
        ListNode p = head, q = mid.next;
        mid.next = null;
        return mergeSort(sortList(p), sortList(q));
    }

    public ListNode getMid(ListNode head) {
        ListNode s = head, f = head.next;
        while (f != null && f.next != null) {
            s = s.next;
            f = f.next.next;
        }
        return s;
    }

    public ListNode mergeSort(ListNode l1, ListNode l2) {
        if (l1 == null || l2 == null) return l1 == null ? l2 : l1;
        ListNode dummy = new ListNode(-1);
        ListNode cur = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) {
                cur.next = l1;
                l1 = l1.next;
            } else {
                cur.next = l2;
                l2 = l2.next;
            }
            cur = cur.next;
        }
        if (l1 != null) cur.next = l1;
        if (l2 != null) cur.next = l2;
        return dummy.next;
    }
}
```

### [32. 最长有效括号(hard)](https://leetcode-cn.com/problems/longest-valid-parentheses/)

> ```
> 输入：s = ")()())"
> 输出：4
> 解释：最长有效括号子串是 "()()"
> ```

#### 思路：栈

* 维护一个栈，保持栈底元素为当前已遍历的元素中最后一个没有被匹配的右括号的下标；
* 若遇到左括号则下标压栈，若为右括号则弹栈表示匹配；
* 若栈为空，则当前右括号没有被匹配，则压栈；若栈不为空，则更新答案。

时间复杂度：$O(N)$

空间复杂度：$O(N)$

```java
class Solution {
    public int longestValidParentheses(String s) {
        Deque<Integer> stack = new LinkedList<>();
        int ans = 0;
        stack.push(-1);
        for (int i = 0; i < s.length(); ++i) {
            if (s.charAt(i) == '(') stack.push(i);
            else {
                stack.pop();
                if (stack.isEmpty()) stack.push(i);
                else ans = Math.max(ans, i - stack.peek());
            }
        }
        return ans;
    }
}
```

### [113. 路径总和 II(mid)](https://leetcode-cn.com/problems/path-sum-ii/)

> ```
> 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
> 输出：[[5,4,11,2],[5,8,4,5]]
> ```
>
> ![img](https://assets.leetcode.com/uploads/2021/01/18/pathsumii1.jpg)

#### 思路：搜索

时间复杂度：$O(N^2)$

空间复杂度：$O(N)$

```java
class Solution {
    List<List<Integer>> ans = new ArrayList<>();
    List<Integer> path = new ArrayList<>();

    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        dfs(root, targetSum);
        return ans;
    }

    public void dfs(TreeNode root, int targetSum) {
        if (root == null) return;
        path.add(root.val);
        targetSum -= root.val;
        if (root.left == null && root.right == null && targetSum == 0)
            ans.add(new ArrayList<>(path));
        dfs(root.left, targetSum);
        dfs(root.right, targetSum);
        path.remove(path.size() - 1);
    }
}
```

### [18. 四数之和(mid)](https://leetcode-cn.com/problems/4sum/)

> ```
> 输入：nums = [1,0,-1,0,-2,2], target = 0
> 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
> ```

#### 思路：排序+双指针

* 首先对数组进行排序，方便枚举和去重；
* 枚举第一个数：
  * 如果当前数字等于上一个数字，则去重；
  * 如果连续的四个数字和大于 $target$，则不可能满足要求；
  * 如果当前数字加上最大的三个数小于 $target$，则结束当前枚举；
* 枚举第二个数：
  * 操作同上；
  * 双指针遍历最后两个数，同时去重。

时间复杂度：$O(N^3)$

空间复杂度：$O(1)$

```java
class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        int n = nums.length;
        List<List<Integer>> ans = new ArrayList<>();
        if (nums == null || n < 4) return ans;
        Arrays.sort(nums);
        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;
            if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;
                if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target) continue;
                int l = j + 1, r = n - 1;
                while (l < r) {
                    if (nums[i] + nums[j] + nums[l] + nums[r] < target) l++;
                    else if (nums[i] + nums[j] + nums[l] + nums[r] > target) r--;
                    else {
                        ans.add(new ArrayList<>(Arrays.asList(nums[i], nums[j], nums[l], nums[r])));
                        l++;
                        r--;
                        while (l < r && nums[l] == nums[l - 1]) l++;
                        while (l < r && nums[r] == nums[r + 1]) r--;
                    }
                }
            } 
        }
        return ans;
    }
}
```









