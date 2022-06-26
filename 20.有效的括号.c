/*
 * @lc app=leetcode.cn id=20 lang=c
 *
 * [20] 有效的括号
 *
 * https://leetcode.cn/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (44.59%)
 * Likes:    3349
 * Dislikes: 0
 * Total Accepted:    1.1M
 * Total Submissions: 2.5M
 * Testcase Example:  '"()"'
 *
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
 * 
 * 有效字符串需满足：
 * 
 * 
 * 左括号必须用相同类型的右括号闭合。
 * 左括号必须以正确的顺序闭合。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "()"
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "()[]{}"
 * 输出：true
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "(]"
 * 输出：false
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：s = "([)]"
 * 输出：false
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：s = "{[]}"
 * 输出：true
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * s 仅由括号 '()[]{}' 组成
 * 
 * 
 */

// @lc code=start
bool is_left_bracket(char bracket)
{
    return bracket == '(' || bracket == '[' || bracket == '{';
}
char get_match_right_bracket(char bracket)
{
    switch (bracket)
    {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    }
    return '\0';
}

bool isValid(char * s){
    int stack[5000]; // 不需要实现一个实际的栈，用数组表示即可
    int top = -1; // 入栈: top++, 出栈: top--

    /* 遍历字符串 s，
    如果当前字符是左括号，就让它对应的右括号入栈；
    如果当前字符是右括号
        1. 如果它和栈顶的右括号相等，就出栈；
        2. 如果它和栈顶的右括号不相等（或者栈空），说明这个字符串是不匹配的，返回 false；

    遍历完毕，如果栈空，则说明所有括号都成功匹配
    */
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (is_left_bracket(s[i]))
        {
            stack[++top] = get_match_right_bracket(s[i]);
        }
        else
        {
            if (top == -1 ||  s[i] != stack[top])
            {
                return false;
            }
            top--;
        }
    }
    return top == -1;
}
// @lc code=end

