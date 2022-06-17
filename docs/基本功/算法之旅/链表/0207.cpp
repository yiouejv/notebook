

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        bool b1 = true, b2 = true;
        ListNode *cur1 = headA, *cur2 = headB;
        while (cur1 && cur2 && cur1 != cur2) {
            cur1 = cur1->next;
            if (!cur1 && b1) {
                b1 = false;
                cur1 = headB;
            }

            cur2 = cur2->next;
            if (!cur2 && b2) {
                b2 = false;
                cur2 = headA;
            }
        }
        return cur1 == cur2 ? cur1 : nullptr;
    }
};
