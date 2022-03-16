/*
 * @lc app=leetcode.cn id=5 lang=c
 *
 * [5] 最长回文子串
 *
 * https://leetcode-cn.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (36.26%)
 * Likes:    4813
 * Dislikes: 0
 * Total Accepted:    910K
 * Total Submissions: 2.5M
 * Testcase Example:  '"babad"'
 *
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "cbbd"
 * 输出："bb"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 1000
 * s 仅由数字和英文字母组成
 *
 *
 */

// @lc code=start

/**
 * @brief 判断子字符串是否是回文
 *
 * @param s 原始字符串
 * @param start 字串起点下标
 * @param end 字串结束下标
 * @return true 是回文子串
 * @return false 不是回文子串
 */
bool isPalindromicSubString(char *s, int start, int end)
{
    int leftIndex = start;
    int rightIndex = end;

    // 两个指针往中间缩，只要两个指针指向的元素不相等，那就不是回文
    while (leftIndex < rightIndex)
    {
        if (s[leftIndex] != s[rightIndex])
            return false;
        leftIndex++;
        rightIndex--;
    }
    return true;
}

char *longestPalindrome(char *s)
{
    // 暴力破解
    /**
     * 首先回文要求对称，以 s[0] 作为首部
     * 从最右边开始往左找，有没有和 s[0] 一样的字符 s[x]
     * 如果有，再看s[1]和s[x-1] 能不能符合，以此类推
     */
    // tips：如果目前找到的最长回文子串的长度已经比还没遍历的的部分大了，那就没有遍历的必要了（i=2 的时候，能找到的子串最长是 length-i，所以如果 maxlength>=length-i，那就可以结束遍历了)

    // 算一下多长
    int length = strlen(s);

    // 返回字符串（动态分配,要留一个 '\0' 的位置)
    char *returnString;
    returnString = (char *)malloc((1024) * sizeof(char));

    memset(returnString, '\0', sizeof(returnString));

    // 一个字符处理
    if (length == 1)
    {
        memcpy(returnString, s, 1);
        return returnString;
    }

    // 最长回文子串的长度
    int longestPalindromicSubStringLength = 0;
    // 最长回文子串的起始坐标
    int longestPalindromicSubStringStartIndex = 0;

    // 逐个遍历
    for (int start = 0; start < length; start++)
    {
        // 剩下的部分比已经找到的字串短，没有继续的必要
        if (longestPalindromicSubStringLength >= length - start)
            break;

        // 逐一验证以 s[start] 为首，以 s[end] 为最后一个字符的字符串是否为回文
        for (int end = length - 1; start < end; end--)
        {

            // 如果现在遍历到的这个子串是回文串，而且长度还比之前找到的字串更长
            if (isPalindromicSubString(s, start, end) && (end - start + 1) > longestPalindromicSubStringLength)
            {

                // 记录它
                longestPalindromicSubStringLength = end - start + 1;
                longestPalindromicSubStringStartIndex = start;
                // 跳出这轮循环（这个子串的长度是递减的，没有再往里找的必要了）
                break;
            }
        }
    }

    memcpy(returnString, s + longestPalindromicSubStringStartIndex, longestPalindromicSubStringLength);

    // 为什么要这样？不知道，甚至之前的memset还不能动，会报错
    returnString[longestPalindromicSubStringLength] = '\0';
    // 如果找不到任何回文，就返回第一个字符
    if (returnString[0] == '\0')
        returnString[0] = s[0];
    return returnString;
}
// @lc code=end
