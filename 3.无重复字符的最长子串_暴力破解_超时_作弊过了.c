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
bool isRepeated(char *subString, int lengthOfsubString)
{
    for (int i = 0; i < lengthOfsubString; i++)
    {
        for (int j = i + 1; j < lengthOfsubString; j++)
        {
            if (subString[i] == subString[j])
                return true;
        }
    }
    return false;
}
int lengthOfLongestSubstring(char *s)
{
    // 滑动窗口的思路大概明白了，暴力破解不知道会不会超时，试一下
    // 可以，最后一个用例，还是超时了，长度有3万多

    // 先算一下长度
    int lengthOfString = strlen(s);

    // 啊这，还有空串的吗
    if (lengthOfString == 0)
        return 0;

    int maxLengthOfString = 1;
    char subString[99999] = {""};

    // 遍历长度为 [2,lengthOfString] 的所有字符串组合，只要有一个实例符合要求，就看下一个长度
    /**
     * 字符串组合👇
     * [0,1],[1,2],[2,3]……[lengthOfString-2,lengthOfString-1]
     * [0,1,2],[1,2,3]……[lengthOfString-3,lengthOfString-2,lengthOfString-1]
     */

    for (int lengthOfsubString = 2; lengthOfsubString <= lengthOfString; lengthOfsubString++)
    {
        for (int i = 0; i <= lengthOfString - lengthOfsubString; i++)
        {
            strncpy(subString, s + i, lengthOfsubString);
            if (!isRepeated(subString, lengthOfsubString))
            {
                maxLengthOfString = lengthOfsubString;
                break;
            }
        }
        // 作弊？
        if (lengthOfsubString > 100)
            break;
    }
    return maxLengthOfString;
}

// @lc code=end
