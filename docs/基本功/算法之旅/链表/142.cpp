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
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next || !head->next->next) {
            return nullptr;
        }

        // slow 每次走一步，fast 每次走两步
        ListNode *slow = head, *fast = head->next->next;
        while (slow && fast && slow != fast) {
            slow = slow->next;
            fast = fast->next;
            if (fast) {
                fast = fast->next;
            }
        }
        if (!slow || !fast) {
            return nullptr;
        }

        // 找出环的长度
        int len = 1;
        slow = slow->next;
        while (slow != fast) {
            len ++;
            slow = slow->next;
        }

        // 找出环的入口点
        slow = head, fast = head;
        while (len-- > 0) {
            slow = slow->next;
        }
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
