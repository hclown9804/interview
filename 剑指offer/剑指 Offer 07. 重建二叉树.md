### 代码

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    unordered_map<int, int> hash;
    vector<int> preorder, inorder;
    
    TreeNode* buildTree(vector<int>& _preorder, vector<int>& _inorder) {
        preorder = _preorder, inorder = _inorder;
        for (int i = 0; i < inorder.size(); ++i) hash[inorder[i]] = i;
        return dfs(0, preorder.size() - 1, 0, inorder.size() - 1);
    }
    
    TreeNode* dfs(int pl, int pr, int il, int ir) {
        if (pl > pr) return NULL;
        auto root = new TreeNode(preorder[pl]);
        int k = hash[root->val];
        auto left = dfs(pl + 1, pl + k - il, il, k - 1);
        auto right = dfs(pl + k - il + 1, pr, k + 1, ir);
        root->left = left, root->right = right;
        return root;
    }
};
```

