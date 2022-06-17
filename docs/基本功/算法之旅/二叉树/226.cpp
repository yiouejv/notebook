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
// 递归
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        InvertNode(root);
        return root;
    }

private:
    void InvertNode(TreeNode *root) {
        if (!root) {
            return;
        }
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;

        InvertNode(root->left);
        InvertNode(root->right);
    }
};

// 广度优先
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> que;
        if (root) que.push(root);
        while (!que.empty()) {
            TreeNode *cur = que.front();
            que.pop();
            swap(cur->left, cur->right);
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
        }
        return root;
    }
};
