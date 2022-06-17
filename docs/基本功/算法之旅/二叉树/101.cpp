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
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return compare(root->left, root->right);
    }
private:
    bool compare(TreeNode *left, TreeNode *right) {
        if (left == nullptr && right == nullptr) {
            return true;
        } else if (left == nullptr || right == nullptr) {
            return false;
        } else if (left->val != right->val) {
            return false;
        }
        return compare(left->left, right->right) && compare(left->right, right->left);
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        queue<TreeNode*> que;
        que.push(root->left); que.push(root->right);

        while (!que.empty()) {
            TreeNode *node1 = que.front(); que.pop();
            TreeNode *node2 = que.front(); que.pop();
            if (!node1 && !node2) continue;  // continue
            else if (!node1 || !node2) return false;
            else if (node1->val != node2->val) return false;

            que.push(node1->left); que.push(node2->right);
            que.push(node1->right); que.push(node2->left);
        }
        return true;
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        stack<TreeNode*> sta;
        sta.push(root->left); sta.push(root->right);

        while (!sta.empty()) {
            TreeNode *node1 = sta.top(); sta.pop();
            TreeNode *node2 = sta.top(); sta.pop();
            if (!node1 && !node2) continue;  // continue
            else if (!node1 || !node2) return false;
            else if (node1->val != node2->val) return false;

            sta.push(node1->left); sta.push(node2->right);
            sta.push(node1->right); sta.push(node2->left);
        }
        return true;
    }
};
