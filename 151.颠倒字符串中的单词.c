/*
 * @lc app=leetcode.cn id=151 lang=c
 *
 * [151] 颠倒字符串中的单词
 *
 * https://leetcode.cn/problems/reverse-words-in-a-string/description/
 *
 * algorithms
 * Medium (50.39%)
 * Likes:    571
 * Dislikes: 0
 * Total Accepted:    262K
 * Total Submissions: 519.4K
 * Testcase Example:  '"the sky is blue"'
 *
 * 给你一个字符串 s ，颠倒字符串中 单词 的顺序。
 *
 * 单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
 *
 * 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
 *
 * 注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "the sky is blue"
 * 输出："blue is sky the"
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "  hello world  "
 * 输出："world hello"
 * 解释：颠倒后的字符串中不能存在前导空格和尾随空格。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "a good   example"
 * 输出："example good a"
 * 解释：如果两个单词间有多余的空格，颠倒后的字符串需要将单词间的空格减少到仅有一个。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^4
 * s 包含英文大小写字母、数字和空格 ' '
 * s 中 至少存在一个 单词
 *
 *
 *
 *
 *
 *
 *
 * 进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 O(1) 额外空间复杂度的 原地 解法。
 *
 */

// @lc code=start


void reverseString(char *s, int sSize)
{
    int left = 0;
    int right = sSize - 1;
    char temp;
    while (left < right)
    {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++, right--;
    }
}

char *reverseWords(char *s)
{
    // printf("strlen(s) = %d\n", strlen(s));
    char *ret = (char *)malloc(sizeof(char) * strlen(s) + 1);
    memset(ret, 0, sizeof(char) * strlen(s) + 1);

    int left = 0;
    int right = 0;
    int s_index = 0;
    int ret_index = 0;

    while (s_index < strlen(s))
    {
        left = s_index; // 从新的位置开始遍历

        /* 跳过左侧的空格 */
        while (left < strlen(s) && s[left] == ' ')
            left++;

        /* 遍历到了最后，说明上一次遍历到了最后一个单词 */
        if (left == strlen(s))
        {
            ret[ret_index - 1] = '\0'; // 把最后一个空格去掉
            break;                     //然后跳出循环
        }

        /* 找到一个单词的结尾，范围：[left, right) */
        right = left;
        while (s[right] != ' ' && s[right] != '\0')
            right++;

        s_index = right;

        // printf("left: %d, right: %d\n", left, right);
        /* [left, right) 倒序写入结果数组 */
        while (right > left)
            ret[ret_index++] = s[--right];

        /* 如果没遍历到最后，补空格 */
        if (s_index != strlen(s))
            ret[ret_index++] = ' ';
    }

    /* 反转整个 ret 字符串 */
    reverseString(ret, strlen(ret));


    return ret;
}
// @lc code=end
