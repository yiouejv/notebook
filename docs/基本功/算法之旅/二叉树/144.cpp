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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        Traversal(root, ans);
        return ans;
    }

private:
    void Traversal(TreeNode *root, vector<int> &ans) {
        if (root == nullptr) {
            return;
        }
        ans.push_back(root->val);  // 先根
        Traversal(root->left, ans);  // 左
        Traversal(root->right, ans);  // 右
    }
};


class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> sta;
        sta.push(root);

        while (!sta.empty()) {
            TreeNode *node = sta.top();
            sta.pop();

            if (node) {
                ans.push_back(node->val);
                sta.push(node->right);
                sta.push(node->left);
            }
        }
        return ans;
    }
};
