/*
 * @lc app=leetcode.cn id=9 lang=c
 *
 * [9] 回文数
 *
 * https://leetcode-cn.com/problems/palindrome-number/description/
 *
 * algorithms
 * Easy (57.68%)
 * Likes:    1892
 * Dislikes: 0
 * Total Accepted:    950.1K
 * Total Submissions: 1.7M
 * Testcase Example:  '121'
 *
 * 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 *
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 *
 *
 * 例如，121 是回文，而 123 不是。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：x = 121
 * 输出：true
 *
 *
 * 示例 2：
 *
 *
 * 输入：x = -121
 * 输出：false
 * 解释：从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
 *
 *
 * 示例 3：
 *
 *
 * 输入：x = 10
 * 输出：false
 * 解释：从右向左读, 为 01 。因此它不是一个回文数。
 *
 *
 *
 *
 * 提示：
 *
 *
 * -2^31 <= x <= 2^31 - 1
 *
 *
 *
 *
 * 进阶：你能不将整数转为字符串来解决这个问题吗？
 *
 */

// @lc code=start

bool isPalindrome(int x)
{

    //! 写非字符串方式的时候才反应过来，负数压根不用考虑，直接返回false就行了😵

    // 第一个想法肯定是直接转成字符串，然后判断一下就完事了

    char num[12];

    // 转字符串
    sprintf(num, "%d", x);

    /**
     * 121：left=0,right=2;  left=right=1  *true*
     *
     * 1111: left=0,right=3;  left=1,right=2; left=2,right=1  *true*
     *
     * -121：left=0,right=3  *false*
     *
     * 123421: left=0,right=5;  left=1,right=4; left=2,right=3  *false*
     */

    // 回文判断
    int left = 0;
    int right = strlen(num) - 1;
    while (left < right)
    {
        if (num[left++] != num[right--])
            return false;
    }
    return true;
}
// @lc code=end
