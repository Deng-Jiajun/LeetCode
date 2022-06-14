/*
 * @lc app=leetcode.cn id=541 lang=c
 *
 * [541] 反转字符串 II
 *
 * https://leetcode.cn/problems/reverse-string-ii/description/
 *
 * algorithms
 * Easy (59.40%)
 * Likes:    306
 * Dislikes: 0
 * Total Accepted:    120.2K
 * Total Submissions: 202.4K
 * Testcase Example:  '"abcdefg"\n2'
 *
 * 给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。
 *
 *
 * 如果剩余字符少于 k 个，则将剩余字符全部反转。
 * 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "abcdefg", k = 2
 * 输出："bacdfeg"
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "abcd", k = 2
 * 输出："bacd"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^4
 * s 仅由小写英文组成
 * 1 <= k <= 10^4
 *
 *
 */

// @lc code=start

void reverseString(char *s, int sSize)
{
    int left = 0;
    int right = sSize - 1;
    char temp;
    while (left < right)
    {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++, right--;
    }
}

char *reverseStr(char *s, int k)
{
    /* 一个大小为 2k 的窗口 */
    int left = 0;
    int right = 2 * k + 1;
    const int length = strlen(s);

    while (right < length)
    {
        /* 反转前 k 个字符 */
        reverseString(s + left, k);
        left += 2 * k;
        right += 2 * k;
    }

    /* 剩余部分处理（从 left 到 length - 1） */
    if (length - left < k)                      // 剩余字符少于 k 个
        reverseString(s + left, length - left); // 剩余字符全部反转
    else                                        // 剩余字符大于等于 k 个
        reverseString(s + left, k);             // 反转前 k 个字符

    return s;
}
// @lc code=end
