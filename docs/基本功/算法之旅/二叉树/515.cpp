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
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode*> que;
        if (root) {
            que.push(root);
        }
        while (!que.empty()) {
            int size = que.size();
            int maxVal = INT_MIN;
            for (int i = 0; i < size; ++i) {
                TreeNode *cur = que.front();
                que.pop();

                maxVal = max(maxVal, cur->val);
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
            }
            ans.push_back(maxVal);
        }
        return ans;
    }
};
