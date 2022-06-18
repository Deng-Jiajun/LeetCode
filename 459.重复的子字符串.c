/*
 * @lc app=leetcode.cn id=459 lang=c
 *
 * [459] 重复的子字符串
 *
 * https://leetcode.cn/problems/repeated-substring-pattern/description/
 *
 * algorithms
 * Easy (50.84%)
 * Likes:    714
 * Dislikes: 0
 * Total Accepted:    120.5K
 * Total Submissions: 236.8K
 * Testcase Example:  '"abab"'
 *
 * 给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: s = "abab"
 * 输出: true
 * 解释: 可由子串 "ab" 重复两次构成。
 *
 *
 * 示例 2:
 *
 *
 * 输入: s = "aba"
 * 输出: false
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "abcabcabcabc"
 * 输出: true
 * 解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)
 *
 *
 *
 *
 * 提示：
 *
 *
 *
 *
 * 1 <= s.length <= 10^4
 * s 由小写英文字母组成
 *
 *
 */

// @lc code=start
// #include<string.h>
bool repeatedSubstringPattern(char *s)
{
    /* 组成去头去尾的 s+s */
    const int len=strlen(s);
    char str[len * 2];
    memset(str, 0, sizeof(str));
    strcpy(str, s+1);
    strcat(str, s);
    str[len * 2 - 2] = '\0';
    // printf("%s\n", str);

    /* 判断 str 是否包含 s */
    return strstr(str, s) != NULL;
}
// @lc code=end
