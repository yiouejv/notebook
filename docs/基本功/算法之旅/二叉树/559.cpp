/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

// 广度优先，数有多少层节点
class Solution {
public:
    int maxDepth(Node* root) {
        if (!root) {
            return 0;
        }
        queue<Node*> que;
        que.push(root);
        int ans = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                Node *cur = que.front(); que.pop();
                for (auto node : cur->children) {
                    que.push(node);
                }
            }
            ++ans;
        }
        return ans;
    }
};
