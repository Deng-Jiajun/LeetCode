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

/**
 * 其他的方法
 * 1. 直接把这个数翻转（逐位取模*10），然后判断两个数是否相等
 *      （可能出现溢出的情况，因为给的是 int，所以用 long 存就没事了，
 *          如果不是 C 语言，可以 try-catch 捕获异常，返回 false）
 * 
 * 2.同样是翻转，但是是转换成字符串再翻转，直接用现成的库（显然C语言做不到）
 * 
 */


bool isPalindrome(int x)
{

    // 如果不用字符串，最朴素的想法就是每一位记下来

    // 负数有负号，不可能是回文数，直接返回
    if (x < 0)
        return false;

    // 所以判断的只可能是正数

    // 首先个位数是回文数，直接返回就行了
    if (x < 10)
        return true;

    // 这个数最长是10位，会记录实际长度，不需要初始化
    int nums[10];

    // 记录长度
    int length = 0;

    // 因为看的是回文，所以不需要从第一位开始获取
    // 所以每次对10取模，然后再除10就行了

    // 把数字逐位倒序写入 nums[]
    while (x != 0)
    {
        nums[length++] = x % 10;
        x = x / 10;
    }

    // 和字符串方式一样，进行回文判断即可
    int left = 0;
    int right = length - 1;
    while (left < right)
    {
        if (nums[left++] != nums[right--])
            return false;
    }
    return true;
}
// @lc code=end
