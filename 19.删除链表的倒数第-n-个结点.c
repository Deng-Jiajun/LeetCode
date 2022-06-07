/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第 N 个结点
 *
 * https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 *
 * algorithms
 * Medium (44.13%)
 * Likes:    2069
 * Dislikes: 0
 * Total Accepted:    808K
 * Total Submissions: 1.8M
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：head = [1,2,3,4,5], n = 2
 * 输出：[1,2,3,5]
 *
 *
 * 示例 2：
 *
 *
 * 输入：head = [1], n = 1
 * 输出：[]
 *
 *
 * 示例 3：
 *
 *
 * 输入：head = [1,2], n = 1
 * 输出：[1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 链表中结点的数目为 sz
 * 1 <= sz <= 30
 * 0 <= Node.val <= 100
 * 1 <= n <= sz
 *
 *
 *
 *
 * 进阶：你能尝试使用一趟扫描实现吗？
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

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    int i = 1;

    /* 让快指针先走 n+1 步 */
    while (i <= n + 1 && fast)
    {
        fast = fast->next;
        i++;
    } /* fast 指向第 n+2（也是 i） 个节点，slow 指向第 1 个节点 */

    /* 如果直接遍历到最后了 */
    if (!fast)
    {
        /* 😵 逻辑到这里脑子已经成糨糊了，但是 AC 了，应该没问题 */

        /* 这时 i-1 就是链表的长度 */
        /* 有两种可能：
        1. i-1 == n，那么就删除头节点
        2. i-1 == n+1，那就删除第二个节点
        */
        if (i - 1 == n)
        {
            head = head->next;
            // free(slow);
            return head;
        }
        if (i - 1 == n + 1)
        {
            head->next = head->next->next;
            return head;
        }
    }

    /* 快慢指针同时走 */
    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
    } /* fast 指向 NULL（倒数第 0 个节点（倒数第 1 之后）），slow 指向倒数第 n+1 个节点 */

    /* 移除 slowslow->next 指向的节点 */
    slow->next = slow->next->next;
    return head;
}
// @lc code=end
