/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        queue<Node*> que;
        if (root) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            Node *pre = nullptr;
            Node *cur = nullptr;
            for (int i = 0; i < size; ++i) {
                cur = que.front();
                que.pop();
                if (pre) pre->next = cur;
                if (cur->left) que.push(cur->left);
                if (cur->right) que.push(cur->right);
                pre = cur;
            }
        }
        return root;
    }
};
