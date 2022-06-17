/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        int ans = 0;
        queue<TreeNode*> que;
        if (root) que.push(root);
        while (!que.empty()) {
            TreeNode *cur = que.front(); que.pop();
            ++ans;
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
        }
        return ans;
    }
};
