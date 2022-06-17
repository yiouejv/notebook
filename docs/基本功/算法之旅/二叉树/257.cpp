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
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) {
            return {};
        }
        vector<string> ans;
        vector<int> path;
        dfs(root, ans, path);
        return ans;
    }

    void dfs(TreeNode *node, vector<string> &ans, vector<int> &path) {
        path.push_back(node->val);

        if (!node->left && !node->right) {
            ans.push_back(GetPathString(path));
            return;
        }

        if (node->left) {
            dfs(node->left, ans, path);
            path.pop_back();
        }

        if (node->right) {
            dfs(node->right, ans, path);
            path.pop_back();
        }
    }

    string GetPathString(vector<int> path) {
        string ret;
        int i = 0;
        for (i = 0; i < path.size() - 1; ++i) {
            ret += to_string(path[i]);
            ret += "->";
        }
        ret += to_string(path[i]);
        return ret;
    }
};
