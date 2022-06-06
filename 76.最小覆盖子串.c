/*
 * @lc app=leetcode.cn id=76 lang=c
 *
 * [76] 最小覆盖子串
 *
 * https://leetcode.cn/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (44.21%)
 * Likes:    1917
 * Dislikes: 0
 * Total Accepted:    294.1K
 * Total Submissions: 665.1K
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 ""
 * 。
 *
 *
 *
 * 注意：
 *
 *
 * 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
 * 如果 s 中存在这样的子串，我们保证它是唯一的答案。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "ADOBECODEBANC", t = "ABC"
 * 输出："BANC"
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "a", t = "a"
 * 输出："a"
 *
 *
 * 示例 3:
 *
 *
 * 输入: s = "a", t = "aa"
 * 输出: ""
 * 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
 * 因此没有符合条件的子字符串，返回空字符串。
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * s 和 t 由英文字母组成
 *
 *
 *
 * 进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？
 */

// @lc code=start

/**
 * @brief 判断 num_substring 对应的字符串是否是 num_string 对应字符串的覆盖子串
 *
 * @param num_string 对应某个字符串的每个字符数量的映射数组
 * @param num_substring 对应某个子串的每个字符数量的映射数组
 *
 * @retval true 对应的字符串是 num_zone 对应字符串的覆盖子串
 * @retval false 对应的字符串不是 num_zone 对应字符串的覆盖子串
 */
bool isCoverSubstring(const int *num_string, const int *num_substring)
{
    /* 实际含义是：substring 中的每个字符都能在 string 中找到，且数量更少 */
    /* 具体做法是判断 num_substring 的每一项是不是都小于等于 num_string 的对应项 */
    for (int i = 65; i < 123; i++) // A=65 z=122
    {
        if (num_substring[i] > num_string[i])
        {
            return false;
        }
    }
    return true;
}

char *minWindow(char *s, char *t)
{
    if (strlen(t) > strlen(s)) /* 长度都不满足，直接返回空字符串 */
        return "";

    int left = 0;
    int right = 0;
    int min_len = strlen(s) + 1; // 最小子串的长度
    int min_index = 0;           // 最小子串的起始下标

    int num_t[128] = {0};    // t 中每个字符的数量，对应 ASCII 码表，A=65 z=122
    int num_zone[128] = {0}; // 选定区域内每个字符的数量

    /* 计算 t 中每个字符的数量 */
    for (int i = 0; t[i] != '\0'; i++)
    {
        num_t[t[i]]++;
    }

    while (1)
    {
        if (right == strlen(s)) /* 边界退出 */
            break;

        /* 构建一个区间（zone），使 t 是这个字符串的覆盖子串 */
        /* [left, right) 左闭右开 */
        while (!isCoverSubstring(num_zone, num_t) && right < strlen(s))
        {
            num_zone[s[right]]++;
            right++;
        }
        // break;
        /* 检查该子串是否满足要求 */
        if (isCoverSubstring(num_zone, num_t)) /* 如果满足 */
        {
            /* 左边界右移，压缩符合要求的子串至最小 */
            while (isCoverSubstring(num_zone, num_t))
            {
                num_zone[s[left]]--;
                left++;
            } /* 结束循环时，[left,right) 已不再是覆盖子串 */

            /* 然后判断一下 [left-1,right) 的长度是否更小 */
            if (right - left + 1 < min_len)
            {
                /* 如果长度更小，就更新最小子串的起始下标和长度 */
                min_index = left - 1;
                min_len = right - left + 1; // [left-1,right-1]
            }
        }
        else /* 如果不满足，说明遍历完毕，退出循环 */
        {
            break;
        }
    }

    /* 如果没有找到覆盖子串，则返回空字符串 */
    if (min_len == strlen(s) + 1)
    {
        return "";
    }
    else /* 如果找到了，就返回该子串 */
    {
        char *ret = (char *)malloc(sizeof(char) * (min_len + 1));
        for (int i = 0; i < min_len; i++)
        {
            ret[i] = s[min_index + i];
        }
        ret[min_len] = '\0';
        return ret;
    }
}

// @lc code=end
