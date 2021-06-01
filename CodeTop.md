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
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;
        }
        ListNode p = head, q = reverseList(slow);
        while (q != null) {
            if (p.val != q.val) return false;
            p = p.next;
            q = q.next;
        }
        return true;
    }   

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



