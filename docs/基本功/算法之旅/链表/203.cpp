
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *ans = nullptr;
        if (head == nullptr) {
            return ans;
        }

        // find first node->val != val node || nullptr
        ListNode *node = head;
        while (node && node->val == val) {
            node = node->next;
        }
        ans = node;

        // delete node while node->val == val
        node = head;
        ListNode *pre = nullptr;
        while (node) {
            if (node->val == val) {
                if (pre) {
                    pre->next = node->next;
                    delete node;
                    node = pre->next;
                } else {
                    ListNode *temp = node;
                    node = node->next;
                    delete temp;
                }
            } else {
                pre = node;
                node = node->next;
            }
        }
        return ans;
    }
};


class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *pre = dummy;
        ListNode *cur = head;
        while (cur) {
            if (cur->val == val) {
                ListNode *temp = cur;
                pre->next = cur->next;
                delete temp;
            } else {
                pre = cur;
            }
            cur = cur->next;
        }
        return dummy->next;
    }
};
