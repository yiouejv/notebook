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
    bool isBalanced(TreeNode* root) {
        return GetHeight(root) == -1 ? false : true;
    }
private:
    // 后序遍历求高度, 如果已经不是平衡二叉树了，高度返回-1
    int GetHeight(TreeNode *root) {
        if (!root) return 0;
        int leftHeight = GetHeight(root->left);
        if (leftHeight == -1) return -1;
        int rightHeight = GetHeight(root->right);
        if (rightHeight == -1) return -1;

        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        return 1 + max(leftHeight, rightHeight);
    }
};
