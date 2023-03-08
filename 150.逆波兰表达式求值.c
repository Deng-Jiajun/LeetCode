/*
 * @lc app=leetcode.cn id=150 lang=c
 *
 * [150] 逆波兰表达式求值
 *
 * https://leetcode.cn/problems/evaluate-reverse-polish-notation/description/
 *
 * algorithms
 * Medium (53.72%)
 * Likes:    559
 * Dislikes: 0
 * Total Accepted:    195.9K
 * Total Submissions: 364.7K
 * Testcase Example:  '["2","1","+","3","*"]'
 *
 * 根据 逆波兰表示法，求表达式的值。
 *
 * 有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
 *
 * 注意 两个整数之间的除法只保留整数部分。
 *
 * 可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：tokens = ["2","1","+","3","*"]
 * 输出：9
 * 解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
 *
 *
 * 示例 2：
 *
 *
 * 输入：tokens = ["4","13","5","/","+"]
 * 输出：6
 * 解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
 *
 *
 * 示例 3：
 *
 *
 * 输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
 * 输出：22
 * 解释：该算式转化为常见的中缀算术表达式为：
 * ⁠ ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= tokens.length <= 10^4
 * tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数
 *
 *
 *
 *
 * 逆波兰表达式：
 *
 * 逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
 *
 *
 * 平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
 * 该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
 *
 *
 * 逆波兰表达式主要有以下两个优点：
 *
 *
 * 去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
 * 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
 *
 *
 */
#include <stdbool.h>
// @lc code=start

/* 根据题目的意思，不是操作符就是数字 */
bool is_operator(const char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/* 根据左右操作数和操作符，计算结果并返回 */
int calc(int left, int right, char operator)
{
    switch (operator)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        return 0;
    }
}

/**
 * @brief 字符串转整数
 * 
 * @param s 指向要转换的字符串
 * @return int 转换后的整数
 */
int string_to_int(const char *s)
{
    int result = 0;
    while (*s != '\0')
    {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result;
}

int evalRPN(char **tokens, int tokensSize)
{
    int stack[tokensSize];
    int top = -1;
    // for (int i = 0; i < tokensSize; i++)
    // {
    //     printf("%d ", tokens[i][0]);
    // }

    /* 遍历整个 tokens */
    for (int i = 0; i < tokensSize; i++)
    {
        /* 如果当前字符是操作符，就取出栈顶两个数字进行计算 */
        if (is_operator(tokens[i][0]))
        {
            /* 取左右操作数 */
            int left = stack[top - 1];
            int right = stack[top];

            /* 计算、压栈 */
            stack[top - 1] = calc(left, right, tokens[i][0]);
            top--;
        }
        else /* 如果当前字符是数字，就压栈 */
        {
            stack[++top] = string_to_int(tokens[i]);
        }

        for (int i = 0; i < tokensSize; i++)
        {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
    return stack[0];
}
// @lc code=end
