/*
 * @lc app=leetcode.cn id=28 lang=c
 *
 * [28] 实现 strStr()
 *
 * https://leetcode.cn/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (40.69%)
 * Likes:    1458
 * Dislikes: 0
 * Total Accepted:    665.3K
 * Total Submissions: 1.6M
 * Testcase Example:  '"hello"\n"ll"'
 *
 * 实现 strStr() 函数。
 *
 * 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0
 * 开始）。如果不存在，则返回  -1 。
 *
 * 说明：
 *
 * 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
 *
 * 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java 的 indexOf()
 * 定义相符。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：haystack = "hello", needle = "ll"
 * 输出：2
 *
 *
 * 示例 2：
 *
 *
 * 输入：haystack = "aaaaa", needle = "bba"
 * 输出：-1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= haystack.length, needle.length <= 10^4
 * haystack 和 needle 仅由小写英文字符组成
 *
 *
 */

// @lc code=start

/**
 * @brief 计算模式串的 sunday 算法对应的偏移表
 *
 * @param str 模式串
 * @return int* 偏移表
 */
int *sunday_offset(const char *str)
{
    /* 全小写字母，长度 26 就够了 */
    int *offset = (int *)malloc(sizeof(int) * 26);

    /* 找 a~z 的偏移（离末尾的距离 + 1） */
    for (int i = 0; i < 26; i++)
    {
        /* 直接从后往前找，找到第一个就行 */
        int j;
        for (j = strlen(str) - 1; j >= 0; j--)
        {
            if (str[j] == 'a' + i)
            {
                break;
            }
        }
        /* 不管有没有，都要记录偏移值 */
        offset[i] = strlen(str) - j;
    }

    return offset;
}

int strStr(char *haystack, char *needle)
{
    /* 如果模式串是空字符串，返回 0 */
    if (!needle[0])
        return 0;

    /* 如果匹配串长度小于模式串长度，返回 -1 */
    if (strlen(haystack) < strlen(needle))
        return -1;

    int *offset = sunday_offset(needle);

    // /* 看一下偏移表的内容 */
    // for (int i = 0; i < 26; i++)
    // {
    //     printf("%d ", offset[i]);
    // }

    /* 根据编译表进行匹配 */
    int i = 0;
    while (i <= strlen(haystack) - strlen(needle))
    {
        bool match = true;
        /* 逐位匹配 */
        for (int j = 0; j < strlen(needle); j++)
        {
            if (haystack[i + j] != needle[j])
            {
                /* 有一位不匹配，就退出 */
                match = false;
                break;
            }
        }

        if (match) //如果匹配上了，就返回
        {
            return i;
        }
        else // 没匹配上，就按偏移表偏移
        {
            // haystack[i + strlen(needle) 会越界，要做判断
            if (i + strlen(needle) < strlen(haystack))
            {
                i += offset[haystack[i + strlen(needle)] - 'a'];
            }
            else
            {
                break;
            }
        }
    }

    return -1; // 没找到，返回 -1
}
// @lc code=end
