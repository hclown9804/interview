/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
    dfs：时间复杂度O(n)
    遍历时往上传递当前子树的最小值和最大值；首先遍历左子树，首先递归判断左子树是否合法，
    然后判断左子树的最大值是否小于当前节点值，更新最大值最小值，遍历右子树同理。
*/

class Solution {
public:
    bool dfs(TreeNode* root, int& maxv, int& minv) {
        maxv = minv = root->val;
        if (root->left) {
            int n_maxv, n_minv;
            if (!dfs(root->left, n_maxv, n_minv)) return false;
            if (n_maxv >= root->val) return false;
            maxv = max(n_maxv, maxv);
            minv = min(n_minv, minv);
        }
        if (root->right) {
            int n_maxv, n_minv;
            if (!dfs(root->right, n_maxv, n_minv)) return false;
            if (n_minv <= root->val) return false;
            maxv = max(n_maxv, maxv);
            minv = min(n_minv, minv);
        }
        return true;
    }

    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        int maxv, minv;
        return dfs(root, maxv, minv);
    }
};