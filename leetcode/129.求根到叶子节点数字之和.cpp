/*
 * @lc app=leetcode.cn id=129 lang=cpp
 *
 * [129] 求根到叶子节点数字之和
 */

// @lc code=start
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
    int ans = 0;

    int sumNumbers(TreeNode* root) {
        if (root) dfs(root, 0);
        return ans;
    }

    void dfs(TreeNode* root, int num) {
        num = num * 10 + root->val;
        if (!root->left && !root->right) ans += num;
        if (root->left) dfs(root->left, num);
        if (root->right) dfs(root->right, num);
    }
};
// @lc code=end

