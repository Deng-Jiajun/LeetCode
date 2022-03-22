/*
 * @lc app=leetcode.cn id=367 lang=c
 *
 * [367] 有效的完全平方数
 *
 * https://leetcode-cn.com/problems/valid-perfect-square/description/
 *
 * algorithms
 * Easy (44.85%)
 * Likes:    357
 * Dislikes: 0
 * Total Accepted:    137.6K
 * Total Submissions: 307.1K
 * Testcase Example:  '16'
 *
 * 给定一个 正整数 num ，编写一个函数，如果 num 是一个完全平方数，则返回 true ，否则返回 false 。
 *
 * 进阶：不要 使用任何内置的库函数，如  sqrt 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：num = 16
 * 输出：true
 *
 *
 * 示例 2：
 *
 *
 * 输入：num = 14
 * 输出：false
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 *
 *
 */

// @lc code=start

bool isPerfectSquare(int num)
{

    // 二分查找，有 middle==x/middle 的时候，就返回 ture，否则返回 false

    if (num == 0)
        return false;
    if (num == 1)
        return true;

    int left = 1;
    int right = num/2;
    int middle;

    while (left <= right)
    {
        middle = (left + right) / 2;

        // printf("%d  %d  %d\n", left, right, middle);
        // 小了，找右半边
        if (middle < num / middle)
        {
            left = middle + 1;
        }
        // 大了，找左半边
        else if (middle > num / middle)
        {
            right = middle - 1;
        }
        // middle == num/middle
        else
        {
            if (num % middle == 0)
                return true;
            else
                return false;
        }
    }

    return false;
}
// @lc code=end
