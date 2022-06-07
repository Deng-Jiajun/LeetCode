/*
 * @lc app=leetcode.cn id=24 lang=c
 *
 * [24] 两两交换链表中的节点
 *
 * https://leetcode.cn/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (70.91%)
 * Likes:    1418
 * Dislikes: 0
 * Total Accepted:    454.1K
 * Total Submissions: 640.3K
 * Testcase Example:  '[1,2,3,4]'
 *
 * 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：head = [1,2,3,4]
 * 输出：[2,1,4,3]
 *
 *
 * 示例 2：
 *
 *
 * 输入：head = []
 * 输出：[]
 *
 *
 * 示例 3：
 *
 *
 * 输入：head = [1]
 * 输出：[1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 链表中节点的数目在范围 [0, 100] 内
 * 0 <= Node.val <= 100
 *
 *
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *swapPairs(struct ListNode *head)
{
    /* 空链表、或只有一个节点，直接返回 */
    if (head == NULL || head->next == NULL)
        return head;

    struct ListNode *ret = head->next; // 返回的链表头结点是第二个节点

    struct ListNode *left;
    struct ListNode *right;
    struct ListNode *current = head;

    /* 以两个为一组进行节点交换，所以需要保证两个节点都存在 */
    while (current && current->next) // 短路表达式，不用担心访问越界
    {
        left = current;
        right = current->next;

        /* 左右交换（→） */
        if (right->next && right->next->next)
        {
            /* 如果后面还有一组，交换之后右边会指向新一组的第二个节点 */
            left->next = right->next->next;
        }
        else
        {
            /* 如果没有一组（0或1个节点），就会指向 right->next */
            left->next = right->next; // 它可能是 NULL，也可能不是

            /* 如果是 NULL，那现在已经是最后一组，
                如果不是 NULL，那下一组就剩一个节点 */
        }

        current = right->next; // current 要指向下一组的第一个节点

        /* 左右交换（←） */
        right->next = left;
    }

    return ret;
}
// @lc code=end
