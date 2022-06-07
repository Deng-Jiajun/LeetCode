/*
 * @lc app=leetcode.cn id=206 lang=c
 *
 * [206] 反转链表
 *
 * https://leetcode.cn/problems/reverse-linked-list/description/
 *
 * algorithms
 * Easy (72.99%)
 * Likes:    2559
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 1.5M
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：head = [1,2,3,4,5]
 * 输出：[5,4,3,2,1]
 *
 *
 * 示例 2：
 *
 *
 * 输入：head = [1,2]
 * 输出：[2,1]
 *
 *
 * 示例 3：
 *
 *
 * 输入：head = []
 * 输出：[]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 链表中节点的数目范围是 [0, 5000]
 * -5000
 *
 *
 *
 *
 * 进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
 *
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

struct ListNode *reverseList(struct ListNode *head)
{
    /* 空链表直接返回 */
    if (!head)
        return head;

    struct ListNode *left = head;          // 左侧节点
    struct ListNode *current = head->next; // 当前节点
    struct ListNode *right = NULL;         // 右侧节点

    /* 迭代，把指向逐一翻转 */
    while (current)
    {
        right = current->next; // 得到右侧节点
        current->next = left;  // 当前节点指向左侧节点

        /* 当前节点和左节点整体右移 */
        left = current;
        current = right;
    }
    head->next = NULL;
    head = left;
    return head;
}
// @lc code=end
