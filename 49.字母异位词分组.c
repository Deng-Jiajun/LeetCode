/*
 * @lc app=leetcode.cn id=49 lang=c
 *
 * [49] 字母异位词分组
 *
 * https://leetcode.cn/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (67.31%)
 * Likes:    1161
 * Dislikes: 0
 * Total Accepted:    336.2K
 * Total Submissions: 499.3K
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
 *
 * 字母异位词 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
 * 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * 示例 2:
 *
 *
 * 输入: strs = [""]
 * 输出: [[""]]
 *
 *
 * 示例 3:
 *
 *
 * 输入: strs = ["a"]
 * 输出: [["a"]]
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= strs.length <= 10^4
 * 0 <= strs[i].length <= 100
 * strs[i] 仅包含小写字母
 *
 *
 */

// @lc code=start

/**
 * @brief 判断两个字符串是否是字母异位词
 *
 * @param s
 * @param t
 */
bool isAnagram(char *s, char *t)
{
    /* 不等长，直接返回 false */
    if (strlen(s) != strlen(t))
        return false;

    int count[26] = {0}; // 保存 a-z 的个数

    /* 计算 s 中每个字母出现的次数 */
    for (int i = 0; s[i] != '\0'; i++)
    {
        count[s[i] - 'a']++;
    }

    /* 计算 t 中每个字母出现的次数（直接在 count 里倒扣） */
    for (int i = 0; t[i] != '\0'; i++)
    {
        /* 等长的情况下，如果不匹配，肯定会出现负数 */
        if (--count[t[i] - 'a'] < 0)
            return false;
    }
    return true;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    /* 创建一个数组，记录某个字符串是否被放入了结果数组中 */
    int isIn[strsSize];
    memset(isIn, 0, sizeof(isIn));

    /* 创建一个返回结果的指针数组，由于不知道具体的数量，所以设为最大值 strsSize */
    char ***result = (char ***)malloc(sizeof(char **) * strsSize);

    /* 还要创建一个数组，记录每一组包含字符串的数量。最大值 strsSize */
    *returnColumnSizes = (int *)malloc(sizeof(int) * strsSize);

    int group = 0; // 记录目前找的是第几组字母异位词

    /* 遍历整个 strs，找出所有字符串的字母异位词 */
    for (int i = 0; i < strsSize; i++)
    {
        /* 如果这个字符串没有被放入结果数组中，则放入 */
        if (!isIn[i])
        {
            // printf("lead:%s(i=%d)\n", strs[i], i);
            /* 创建一个数组，记录这个字符串的所有字母异位词。最大值 strsSize */
            result[group] = (char **)malloc(sizeof(char *) * strsSize);
            int order = 0; // 记录目前找的是这一组的第几个字母异位词

            /* 先把这个字符串放到结果数组中 */
            result[group][order] = (char *)malloc(sizeof(char) * (strlen(strs[i]) + 1));
            strcpy(result[group][order], strs[i]);
            isIn[i] = 1;
            order++;

            /* 然后找出这个字符串的所有字母异位词（前面肯定没有了，所以从 i+1 开始找） */
            for (int j = i + 1; j < strsSize; j++)
            {
                /* 如果没被放入结果数组，且是字母异位词，则放入结果数组的同一组内 */
                if (!isIn[j] && isAnagram(strs[i], strs[j]))
                {
                    // printf("follw:%s(j=%d)\n", strs[j], j);
                    result[group][order] = (char *)malloc(sizeof(char) * (strlen(strs[j]) + 1));
                    strcpy(result[group][order], strs[j]);
                    isIn[j] = 1;
                    order++;
                }
            }

            /* 全找出来后记一下这一组的字母异位词的数量 */
            (*returnColumnSizes)[group] = order;

            group++; // group 自增，表示下一组
        }
    }

    /* 整个遍历结束后，记录结果数组的数量 */
    *returnSize = group;

    return result;
}
// @lc code=end
