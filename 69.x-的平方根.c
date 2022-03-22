/*
 * @lc app=leetcode.cn id=69 lang=c
 *
 * [69] x 的平方根
 *
 * https://leetcode-cn.com/problems/sqrtx/description/
 *
 * algorithms
 * Easy (38.91%)
 * Likes:    936
 * Dislikes: 0
 * Total Accepted:    487.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '4'
 *
 * 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
 *
 * 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
 *
 * 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：x = 4
 * 输出：2
 *
 *
 * 示例 2：
 *
 *
 * 输入：x = 8
 * 输出：2
 * 解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= x <= 2^31 - 1
 *
 *
 */

// @lc code=start

int mySqrt(int x)
{
    // 0 和 1，返回它自己
    if (x < 2)
        return x;

    int left = 1;      // 排除了 0 和 1，x 的平方根（的取整）至少是 1
    int right = x / 2; // x 的平方根总小于 x/2（x>4)
    int middle;

    // left和right之间始终差距大于2，
    while (left <= right)
    {
        middle = (left + right) / 2;

        // 值小了
        if (middle < x / middle)
        {
            // 找右半边
            left = middle + 1;
        }
        // 值大了
        else if (middle > x / middle)
        {
            // 找左半边
            right = middle - 1;
        }
        // 刚好是整数根也可能吧
        else
            return middle;
    }

    if (right <= x / right)
        return right;
    else
        return left;
}
// @lc code=end
