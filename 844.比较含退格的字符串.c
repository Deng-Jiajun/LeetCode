/*
 * @lc app=leetcode.cn id=844 lang=c
 *
 * [844] 比较含退格的字符串
 *
 * https://leetcode-cn.com/problems/backspace-string-compare/description/
 *
 * algorithms
 * Easy (50.21%)
 * Likes:    397
 * Dislikes: 0
 * Total Accepted:    122K
 * Total Submissions: 244.6K
 * Testcase Example:  '"ab#c"\n"ad#c"'
 *
 * 给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。# 代表退格字符。
 *
 * 注意：如果对空文本输入退格字符，文本继续为空。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "ab#c", t = "ad#c"
 * 输出：true
 * 解释：s 和 t 都会变成 "ac"。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "ab##", t = "c#d#"
 * 输出：true
 * 解释：s 和 t 都会变成 ""。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "a#c", t = "b"
 * 输出：false
 * 解释：s 会变成 "c"，但 t 仍然是 "b"。
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length, t.length <= 200
 * s 和 t 只含有小写字母以及字符 '#'
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 你可以用 O(n) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？
 *
 *
 */

// @lc code=start

/**
 * @brief 文本处理
 *
 * 处理字符串中的退格字符 '#'，处理成全字符形式，末尾补上 '\0'
 *
 * @param s 要处理的字符串
 */
void TextProcess(char *s)
{
    int i = 0; // 遍历指针
    int j = 0; // 有效字符指针
    while (s[i])
    {
        // 如果不是 '#'，就采用该字符
        if (s[i] != '#')
        {
            s[j++] = s[i];
        }
        // 如果是 '#'，而且 j 不为 0，就让有效指针回退
        // 不知道会不会有一大堆的 '#'，还是判断一下 0 比较保险
        else if (j != 0)
        {
            j--;
        }
        i++;
    }
    // 处理完了之后在末尾补 0
    s[j] = '\0';
}

bool backspaceCompare(char *s, char *t)
{
    // 直接改动原数组，然后比较
    TextProcess(s);
    TextProcess(t);
    return !strcmp(s, t);
}
// @lc code=end
