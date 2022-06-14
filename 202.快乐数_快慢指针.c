/*
 * @lc app=leetcode.cn id=202 lang=c
 *
 * [202] 快乐数
 *
 * https://leetcode.cn/problems/happy-number/description/
 *
 * algorithms
 * Easy (62.87%)
 * Likes:    954
 * Dislikes: 0
 * Total Accepted:    257.3K
 * Total Submissions: 409K
 * Testcase Example:  '19'
 *
 * 编写一个算法来判断一个数 n 是不是快乐数。
 *
 * 「快乐数」 定义为：
 *
 *
 * 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 * 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 * 如果这个过程 结果为 1，那么这个数就是快乐数。
 *
 *
 * 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 19
 * 输出：true
 * 解释：
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 2
 * 输出：false
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 2^31 - 1
 *
 *
 */

// @lc code=start

/* 鬼知道该取什么名字，总之就是逐位的平方求和 */
int calc(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}

bool isHappy(int n)
{
    /* 快慢指针法 */
    /* 不需要做实际上的链表，一个算一次，一个算两次，如果两个相等，就是发现环了 */

    int slow = calc(n);
    int fast = calc(calc(n));
    while (1)
    {
        if (fast == 1 || slow == 1) // 其实肯定是 fast 先到 1
            return true;

        if (fast == slow) // 如果把这个判断放前面会出问题，因为 fast 和 slow 可能都为 1
            return false;

        fast = calc(calc(fast));
        slow = calc(slow);
    }
}
// @lc code=end
