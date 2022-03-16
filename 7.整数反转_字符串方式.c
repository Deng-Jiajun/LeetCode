/*
 * @lc app=leetcode.cn id=7 lang=c
 *
 * [7] 整数反转
 *
 * https://leetcode-cn.com/problems/reverse-integer/description/
 *
 * algorithms
 * Medium (35.17%)
 * Likes:    3431
 * Dislikes: 0
 * Total Accepted:    968.4K
 * Total Submissions: 2.8M
 * Testcase Example:  '123'
 *
 * 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
 *
 * 如果反转后整数超过 32 位的有符号整数的范围 [−2^31,  2^31 − 1] ，就返回 0。
 * 假设环境不允许存储 64 位整数（有符号或无符号）。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：x = 123
 * 输出：321
 *
 *
 * 示例 2：
 *
 *
 * 输入：x = -123
 * 输出：-321
 *
 *
 * 示例 3：
 *
 *
 * 输入：x = 120
 * 输出：21
 *
 *
 * 示例 4：
 *
 *
 * 输入：x = 0
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * -2^31
 *
 *
 */

// @lc code=start

// 写到一半把自己写自闭了，这字符串太麻烦了😫

// 判断给定的这个字符串代表的数字有没有溢出
bool isOverflow(char *num)
{
    // 数字至少有一位，不需要判断是不是空串

    // 如果是负数，而且长度是12
    if (num[0] == '-' && strlen(num) == 11)
    {
        if (strcmp(num, "-2147483648") > 0)
            return true;
    }
    else if (num[0] != '-' && strlen(num) == 10) // 如果是正数，而且长度是11
    {
        if (strcmp(num, "2147483647") > 0)
            return true;
    }

    return false;
}

// int转字符串（顺便反转）
void intToString_AndReverse(int number, char *string)
{

    int index = 0; // 下标，兼数字长度

    // 负数的话加个符号，顺便下标推进一位
    if (number < 0)
    {
        index = 1;
        string[0] = '-';
    }

    // 字符串反转
    if (number < 0) // 负数
    {
        while (number != 0)
        {
            string[index++] = -1 * (number % 10) + '0';
            number /= 10;
        }
    }
    else // 正数
    {
        while (number != 0)
        {
            string[index++] = (number % 10) + '0';
            number /= 10;
        }
    }
}

// 字符串转int
int stringToInt(const char *string)
{
    // 数字至少有一位，不需要判断是不是空串

    int index = 0; // 目前遍历到的下标

    int result = 0; // 运算结果

    /*
     本来打算正负号一起处理，负数最后乘个 -1 就完事了
     然后反应过来负数比整数范围多 1，所以还是得分别处理
     （或者单独判断负数是不是 "-2147483648"，
       不过分别处理正负数应该比每次都判断是不是 "-2147483648" 快一点，吧？)
    */

    // 如果是负数，跳过负号
    if (string[0] == '-')
    {
        index = 1;
        while (index != strlen(string))
        {
            result = result * 10 - (string[index++] - '0');
        }
    }
    else // str如果是正数
    {
        while (index != strlen(string))
        {
            result = result * 10 + (string[index++] - '0');
        }
    }
    return result;
}

int reverse(int x)
{
    // 这题的要点是溢出判断，反转属于基本操作

    // -2^31 = -2147483648
    // 2^31 -1 = 2147483647

    // 0 就直接返回 0 吧，不想在别的地方搞零值判断了
    if (x == 0)
        return 0;

    char num[12] = "0"; // 最长10位，加上负号和'\0'，拢共12位
    intToString_AndReverse(x, num);

    if (isOverflow(num))
        return 0;
    else
        return stringToInt(num);
}
// @lc code=end
