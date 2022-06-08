/*
 * @lc app=leetcode.cn id=438 lang=c
 *
 * [438] 找到字符串中所有字母异位词
 *
 * https://leetcode.cn/problems/find-all-anagrams-in-a-string/description/
 *
 * algorithms
 * Medium (54.58%)
 * Likes:    902
 * Dislikes: 0
 * Total Accepted:    190.5K
 * Total Submissions: 349K
 * Testcase Example:  '"cbaebabacd"\n"abc"'
 *
 * 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
 *
 * 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: s = "cbaebabacd", p = "abc"
 * 输出: [0,6]
 * 解释:
 * 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
 * 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
 *
 *
 * 示例 2:
 *
 *
 * 输入: s = "abab", p = "ab"
 * 输出: [0,1,2]
 * 解释:
 * 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
 * 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
 * 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1 <= s.length, p.length <= 3 * 10^4
 * s 和 p 仅包含小写字母
 *
 *
 */

// @lc code=start

bool isAnagram(char *s, char *t, int t_len)
{
    int count[26] = {0}; // 保存 a-z 的个数

    /* 计算 s 中每个字母出现的次数 */
    for (int i = 0; i != t_len; i++)
    {
        // printf("index1:%d,s[i]-'a':%d\n", i, s[i] - 'a');
        count[s[i] - 'a']++;
    }

    /* 计算 t 中每个字母出现的次数（直接在 count 里倒扣） */
    for (int i = 0; i != t_len; i++)
    {
        // printf("index2:%d,t[i]-'a':%d\n", i, t[i] - 'a');
        /* 等长的情况下，如果不匹配，肯定会出现负数 */
        if (--count[t[i] - 'a'] < 0)
            return false;
    }
    // printf("****true\n");
    return true;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findAnagrams(char *s, char *p, int *returnSize)
{
    /* p 更长，返回空数组 */
    if (strlen(p) > strlen(s))
    {
        *returnSize = 0;
        return NULL;
    }

    int *result = (int *)malloc(sizeof(int) * strlen(s)); // 返回结果
    int index = 0;                                        // 返回结果填到第几个位置

    int sub_str_len = strlen(p);
    for (int i = 0; i <= strlen(s) - strlen(p); i++)
    {
        /* 如果 s[i] 开始的子串和 p 字符串是字母异位词，则将 i 填入结果 */
        if (isAnagram(s + i, p, sub_str_len))
        {
            result[index++] = i;
        }
    }
    *returnSize = index;
    return result;
}
// @lc code=end
