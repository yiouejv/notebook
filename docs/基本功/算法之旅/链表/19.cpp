/*
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 
示例 1：

输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]
 

提示：

链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 

进阶：你能尝试使用一趟扫描实现吗？

*/

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        ListNode *slow = dummy;
        ListNode *quick = head;
        while (--n > 0) {
            quick = quick->next;
        }

        while (quick->next) {
            quick = quick->next;
            slow = slow->next;
        }

        ListNode *temp = slow->next;
        slow->next = temp->next;
        delete temp;
        return dummy->next;
    }
};
