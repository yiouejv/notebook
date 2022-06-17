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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        Traversal(root, ans);
        return ans;
    }
private:
    void Traversal(TreeNode *root, vector<int> &ans) {
        if (root == nullptr) {
            return;
        }
        Traversal(root->left, ans);
        ans.push_back(root->val);
        Traversal(root->right, ans);
    }
};


class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> sta;
        TreeNode *cur = root;

        while (cur != nullptr || !sta.empty()) {
            if (cur) {
                sta.push(cur);  // 左
                cur = cur->left;
            } else {
                cur = sta.top();
                sta.pop();

                ans.push_back(cur->val);  // 中
                cur = cur->right;  // 右
            }
        }
        return ans;
    }
};
