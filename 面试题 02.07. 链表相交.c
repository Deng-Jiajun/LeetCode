// [面试题 02.07. 链表相交]
// (https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    struct ListNode *link_1 = headA, *link_2 = headB;
    while (link_1 != link_2)
    {
        link_1 = link_1 ? link_1->next : headB;
        link_2 = link_2 ? link_2->next : headA;
    }
    return link_1;
}
