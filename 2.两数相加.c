/*
 * @lc app=leetcode.cn id=2 lang=c
 *
 * [2] 两数相加
 *
 * https://leetcode-cn.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (41.39%)
 * Likes:    7616
 * Dislikes: 0
 * Total Accepted:    1.2M
 * Total Submissions: 2.9M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 *
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 *
 *
 * 示例 2：
 *
 *
 * 输入：l1 = [0], l2 = [0]
 * 输出：[0]
 *
 *
 * 示例 3：
 *
 *
 * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * 输出：[8,9,9,9,0,0,0,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 每个链表中的节点数在范围 [1, 100] 内
 * 0
 * 题目数据保证列表表示的数字不含前导零
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

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    // 啊，做加法

    // 先拿指针
    struct ListNode *nodeL1 = l1;
    struct ListNode *nodeL2 = l2;

    // 建个返回链表
    struct ListNode *returnList = malloc(sizeof(struct ListNode));
    // 初始化
    returnList->val = -1;
    returnList->next = NULL;

    // 两个 1 位数，直接算
    if (nodeL1->next == NULL && nodeL2->next == NULL)
    {
        // 相加如果大于 10，要再加个结点
        if ((nodeL1->val + nodeL2->val) >= 10)
        {
            // 加结点
            returnList->next = malloc(sizeof(struct ListNode));
            returnList->next->next = NULL;
            // 赋值
            // 个位
            returnList->val = (nodeL1->val + nodeL2->val) % 10;
            // 十位
            returnList->next->val = (nodeL1->val + nodeL2->val) / 10;
        }
        else // 相加没有大于10，直接改链表值
        {
            returnList->val = nodeL1->val + nodeL2->val;
        }
    }
    else // 不只两位，遍历链表
    {
        // 拿个返回链表的指针
        struct ListNode *node = returnList;

        // 进位符（只能是 0 或 1，为了逻辑逻辑性，实际处理是直接取商）
        int carry = 0;

        // 走循环，开算
        while (nodeL1 != NULL && nodeL2 != NULL)
        {
            node->val = nodeL1->val + nodeL2->val + carry;

            // 如果答案大于等于 10，还得进位
            if (node->val >= 10)
            {
                // 先记进位
                carry = node->val / 10;
                // 再改本位
                node->val = node->val % 10;
            }
            else // 没发生进位，进位符归零
            {
                carry = 0;
            }

            // 两个链表都往后一位
            nodeL1 = nodeL1->next;
            nodeL2 = nodeL2->next;

            // 没有「完全」遍历结束（至少一个链表没有遍历完）
            if (nodeL1 != NULL || nodeL2 != NULL)
            {
                // 先补个点,等着填值
                node->next = malloc(sizeof(struct ListNode));
                node->next->next = NULL;
                node->next->val = -1;

                // 指向返回链表的 node 也往后一位，保证在尾部
                node = node->next;

                // 这个搞太复杂了，做个带头节点的链表应该会更好处理
            }
        }

        // 如果跳出循环，说明 nodeL1 或 nodeL2 至少有一个为 NULL
        // 做情况判断，找到更长的结点
        struct ListNode *longerNode = NULL;

        // L2 已遍历完毕
        if (nodeL1 != NULL && nodeL2 == NULL)
        {
            // 继续遍历 L1
            longerNode = nodeL1;
        }
        // L1 已遍历完毕
        else if (nodeL1 == NULL && nodeL2 != NULL)
        {
            // 继续遍历 L2
            longerNode = nodeL2;
        }
        // L1 和 L2都已遍历完毕
        else
        {
            // 啥也不干，等下面处理一下进位，就结束了
        }
        // 继续遍历更长的链表
        while (longerNode != NULL)
        {
            // 进位符继续用，但是另一个加数始终是 0
            node->val = longerNode->val + 0 + carry;

            // 如果答案大于等于 10，还得进位
            if (node->val >= 10)
            {
                // 先记进位
                carry = node->val / 10;
                // 再改本位
                node->val = node->val % 10;
            }
            else // 没发生进位，进位符归零
            {
                carry = 0;
            }
            // 更长的链表继续向后遍历
            longerNode = longerNode->next;

            // 没有遍历结束
            if (longerNode != NULL)
            {
                // 先补个点,等着填值
                node->next = malloc(sizeof(struct ListNode));
                node->next->next = NULL;
                node->next->val = -1;

                // 指向返回链表的 node 也往后一位，保证在尾部
                node = node->next;
            }
        }
        // 出循环，两个链表都遍历完毕，如果还有进位，还需要再处理一下
        if (carry != 0)
        {
            // 加个结点填值
            node->next = malloc(sizeof(struct ListNode));
            node->next->next = NULL;
            node->next->val = carry;
            node = node->next; // 这句没必要了,只是说,它又回到尾巴了
        }
    }
    return returnList;
    // 还是搞太复杂了，逻辑上看，不如直接算下两个链表各有多长更直观，不见得有太大的开销（最多就 100 个数）
}
// @lc code=end
