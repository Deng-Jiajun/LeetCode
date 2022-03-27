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
 * @brief 找到下一个用来比较的字符的下标
 *
 * @param s 要寻找的字符串
 * @param index 开始的下标（从后往前）
 * @return int 找到的下标（没找到就返回 -1，没找到的意思是前面是空的）
 */
int IndexOfNextChar(char *s, int index)
{
    int skipNum = 0; // 退格次数

    while (index >= 0)
    {
        if (s[index] == '#') // 是退格符，记录
        {
            skipNum++;
        }
        else // 如果不是退格符，看一下要不要退格
        {
            if (skipNum == 0)
            {
                // 不需要退格，那找到了
                return index;
            }
            else
            {
                // 需要退格，那就退格
                skipNum--;
            }
        }

        // 继续往前找
        index--;
    }
    // 没找到就返回 -1
    return -1;
}

bool backspaceCompare(char *s, char *t)
{
    // 从后往前遍历

    // 用来比较的指针
    int sIndex = strlen(s) - 1;
    int tIndex = strlen(t) - 1;
    while (true)
    {
        // 找下一个要比较的字符的下标
        sIndex = IndexOfNextChar(s, sIndex);
        tIndex = IndexOfNextChar(t, tIndex);

        if (sIndex == -1 || tIndex == -1) // 如果其中有至少一个前面的部分是空的
        {
            // 如果都是空的，两个字符串相等，返回 ture
            if (sIndex == -1 && tIndex == -1)
                return true;
            else // 否则二者不相等，返回 false
                return false;
        }
        else // 都不为空，开始判断
        {
            // 这两个字符二者不相等，返回 false
            if (s[sIndex] != t[tIndex])
            {
                return false;
            }
            else // 相等则继续找下一个字符
            {
                // 这一位没问题就往前再找一位
                // 不用担心越界，IndexOfNextChar 发现越界会返回 -1
                sIndex--;
                tIndex--;
            }
        }
    }
}
// @lc code=end
