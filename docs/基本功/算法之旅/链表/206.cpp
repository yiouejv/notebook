
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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *cur = head;
        ListNode *next = cur->next;
        ListNode *nextNode = next->next;
        while (next) {
            nextNode = next->next;
            next->next = cur;
            if (cur == head) {
                head->next = nullptr;
            }
            cur = next;
            next = nextNode;
        }
        return cur;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *pre = nullptr;
        ListNode *cur = head;
        ListNode *temp = nullptr;
        while (cur) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }
};
