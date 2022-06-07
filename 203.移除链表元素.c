/*
 * @lc app=leetcode.cn id=203 lang=c
 *
 * [203] 移除链表元素
 *
 * https://leetcode.cn/problems/remove-linked-list-elements/description/
 *
 * algorithms
 * Easy (53.64%)
 * Likes:    924
 * Dislikes: 0
 * Total Accepted:    367.3K
 * Total Submissions: 684.7K
 * Testcase Example:  '[1,2,6,3,4,5,6]\n6'
 *
 * 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
 *
 *
 * 示例 1：
 *
 *
 * 输入：head = [1,2,6,3,4,5,6], val = 6
 * 输出：[1,2,3,4,5]
 *
 *
 * 示例 2：
 *
 *
 * 输入：head = [], val = 1
 * 输出：[]
 *
 *
 * 示例 3：
 *
 *
 * 输入：head = [7,7,7,7], val = 7
 * 输出：[]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 列表中的节点数目在范围 [0, 10^4] 内
 * 1
 * 0
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

struct ListNode *removeElements(struct ListNode *head, int val)
{
    while (head != NULL && head->val == val)
    {
        head = head->next;
    }

    if (head == NULL)
        return NULL;

    struct ListNode *ret = head;

    while (head->next)
    {
        if (head->next->val == val)
        {
            head->next = head->next->next;
        }
        else
        {
            head = head->next;
        }
    }
    return ret;
}
// @lc code=end
