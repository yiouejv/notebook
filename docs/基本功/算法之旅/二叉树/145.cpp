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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        Traversal(root, ans);
        return ans;
    }

    void Traversal(TreeNode *root, vector<int> &ans) {
        if (root == nullptr) {
            return;
        }

        Traversal(root->left, ans);
        Traversal(root->right, ans);
        ans.push_back(root->val);
    }
};



// 先序遍历, 中左右
// 后序遍历, 左右中, 调整先序遍历的入栈顺序可以成为 中右左
// 最后将 中右左 反转, 得到左右中
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<int> ans;
        stack<TreeNode*> sta;
        sta.push(root);

        while (!sta.empty()) {
            TreeNode *cur = sta.top();
            sta.pop();
            ans.push_back(cur->val);
            if (cur->left) {
                sta.push(cur->left);
            }
            if (cur->right) {
                sta.push(cur->right);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
