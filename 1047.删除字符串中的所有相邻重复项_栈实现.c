/*
 * @lc app=leetcode.cn id=1047 lang=c
 *
 * [1047] 删除字符串中的所有相邻重复项
 *
 * https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/description/
 *
 * algorithms
 * Easy (72.69%)
 * Likes:    398
 * Dislikes: 0
 * Total Accepted:    160.3K
 * Total Submissions: 220.6K
 * Testcase Example:  '"abbaca"'
 *
 * 给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
 *
 * 在 S 上反复执行重复项删除操作，直到无法继续删除。
 *
 * 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
 *
 *
 *
 * 示例：
 *
 * 输入："abbaca"
 * 输出："ca"
 * 解释：
 * 例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串
 * "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= S.length <= 20000
 * S 仅由小写英文字母组成。
 *
 *
 */

// @lc code=start

char *removeDuplicates(char *s)
{
    /* 💡注意结构，直接用数组做栈是不需要反转的，因为它的顺序就是结果的顺序 */
    int *stack = malloc(sizeof(int) * strlen(s) + 1);
    int top = -1;
    /* 遍历整个字符串 s，如果当前字符 s[i] 和栈顶元素相同，则 stack[top] 出栈，
        不相同（或栈空）则 s[i] 入栈 */
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (top == -1 || s[i] != stack[top])
            stack[++top] = s[i];
        else
            top--;
    }

    /* 将栈中元素依次写入 s 中 */
    for (int i = 0; i <= top; i++)
        s[i] = stack[i];

    s[top + 1] = '\0';

    return s;
}
// @lc code=end
