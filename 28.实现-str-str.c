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


int strStr(char *haystack, char *needle) {
    /* 如果 needle 是空字符串，返回 0 */
    if (!needle[0]) return 0;

    /* 如果小于 needle 的长度，返回 -1 */
    if (strlen(haystack) < strlen(needle)) return -1;


    for (int i = 0; i <= strlen(haystack) - strlen(needle); i++) {

        /* 如果这个字符和 needle 的第一个字符相等，则开始比较后续字符 */
        if (haystack[i] == needle[0]) {
            int j = 0;
            while (j < strlen(needle)) {
                if (haystack[i + j] != needle[j])
                    break;
                j++;
            }
            /* 根据 j 的值判断是否找到了 needle */
            if (j == strlen(needle))
                return i;
        }
    }
    return -1;// 没找到，返回 -1
}
// @lc code=end

