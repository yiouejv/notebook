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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) {
            return {};
        }

        queue<TreeNode*> que;
        que.push(root);
        TreeNode *cur = nullptr;
        vector<vector<int>> ans;

        while (!que.empty()) {
            int size = que.size();
            vector<int> vec;

            // 遍历每层的元素
            for (int i = 0; i < size; ++i) {
                cur = que.front();
                que.pop();
                vec.push_back(cur->val);

                if (cur->left) {
                    que.push(cur->left);
                }
                if (cur->right) {
                    que.push(cur->right);
                }
            }
            ans.push_back(vec);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
