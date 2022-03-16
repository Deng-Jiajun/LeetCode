/*
 * @lc app=leetcode.cn id=3 lang=c
 *
 * [3] 无重复字符的最长子串
 *
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (38.53%)
 * Likes:    7023
 * Dislikes: 0
 * Total Accepted:    1.5M
 * Total Submissions: 4M
 * Testcase Example:  '"abcabcbb"'
 *
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: s = "abcabcbb"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 *
 * 示例 2:
 *
 *
 * 输入: s = "bbbbb"
 * 输出: 1
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "pwwkew"
 * 输出: 3
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 * 请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= s.length <= 5 * 10^4
 * s 由英文字母、数字、符号和空格组成
 *
 *
 */

// @lc code=start

// 返回重复元素的下标（相对于子字符串），没找到就返回 -1
int indexOfRepeatedChar(char *subString, int lengthOfsubString, char targetChar)
{
    for (int i = 0; i < lengthOfsubString; i++)
    {
        if (subString[i] == targetChar)
            return i;
    }
    return -1;
}

int lengthOfLongestSubstring(char *s)
{
    // 滑动窗口写法

    // 字符串长度看一下
    int lengthOfString = strlen(s);

    // 先把 空字符串 和 长度为1的字符串 排除在外
    if (lengthOfString == 0)
        return 0;
    if (lengthOfString == 1)
        return 1;

    // 则以下判断以长度 >=2 为前提

    // 设置一个最大长度
    int maxLength = 1;

    // 维持一个不断向前滑动的窗口
    // 设置一个左/右指针（默认 0,1 ）
    //      如果左右指针指向符号不相等
    //          右侧就可以不断向右
    //          比较最大长度，看是否需要改动
    //      如果右指针和窗口内的某个符号相等
    //          左指针移动到那个重复元素之后

    int indexOfLeft = 0;
    int indexOfRight = 1;
    for (; indexOfRight != lengthOfString; indexOfRight++)
    {
        // tips: 当前长度是 indexOfRight - indexOfLeft (要扣掉右指针)

        // 如果没有重复元素
        if (indexOfRepeatedChar((s + indexOfLeft), (indexOfRight - indexOfLeft), s[indexOfRight]) == -1)
        {

            // 变动最大长度（算上右指针）
            if ((indexOfRight - indexOfLeft + 1) > maxLength)
            {
                maxLength = (indexOfRight - indexOfLeft + 1);
            }
        }
        else
        {

            // 如果有重复元素，那就把左指针移动到重复元素之后
            indexOfLeft = indexOfLeft + indexOfRepeatedChar((s + indexOfLeft), (indexOfRight - indexOfLeft), s[indexOfRight]) + 1;
        }
    }
    return maxLength;
}
// @lc code=end
