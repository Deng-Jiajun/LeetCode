/*
 * @lc app=leetcode.cn id=8 lang=c
 *
 * [8] 字符串转换整数 (atoi)
 *
 * https://leetcode-cn.com/problems/string-to-integer-atoi/description/
 *
 * algorithms
 * Medium (21.74%)
 * Likes:    1382
 * Dislikes: 0
 * Total Accepted:    421K
 * Total Submissions: 1.9M
 * Testcase Example:  '"42"'
 *
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
 *
 * 函数 myAtoi(string s) 的算法如下：
 *
 *
 * 读入字符串并丢弃无用的前导空格
 * 检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
 * 读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
 * 将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤
 * 2 开始）。
 * 如果整数数超过 32 位有符号整数范围 [−2^31,  2^31 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −2^31
 * 的整数应该被固定为 −2^31 ，大于 2^31 − 1 的整数应该被固定为 2^31 − 1 。
 * 返回整数作为最终结果。
 *
 *
 * 注意：
 *
 *
 * 本题中的空白字符只包括空格字符 ' ' 。
 * 除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "42"
 * 输出：42
 * 解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
 * 第 1 步："42"（当前没有读入字符，因为没有前导空格）
 * ⁠        ^
 * 第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 * ⁠        ^
 * 第 3 步："42"（读入 "42"）
 * ⁠          ^
 * 解析得到整数 42 。
 * 由于 "42" 在范围 [-2^31, 2^31 - 1] 内，最终结果为 42 。
 *
 * 示例 2：
 *
 *
 * 输入：s = "   -42"
 * 输出：-42
 * 解释：
 * 第 1 步："   -42"（读入前导空格，但忽视掉）
 * ⁠           ^
 * 第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
 * ⁠            ^
 * 第 3 步："   -42"（读入 "42"）
 * ⁠              ^
 * 解析得到整数 -42 。
 * 由于 "-42" 在范围 [-2^31, 2^31 - 1] 内，最终结果为 -42 。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "4193 with words"
 * 输出：4193
 * 解释：
 * 第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
 * ⁠        ^
 * 第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
 * ⁠        ^
 * 第 3 步："4193 with words"（读入 "4193"；由于下一个字符不是一个数字，所以读入停止）
 * ⁠            ^
 * 解析得到整数 4193 。
 * 由于 "4193" 在范围 [-2^31, 2^31 - 1] 内，最终结果为 4193 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0 <= s.length <= 200
 * s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成
 *
 *
 */

// @lc code=start

/*
测试用例
"42"
"   -42"
"4193 with words"
"words and 987"
"-91283472332"
"+-12"
"-+12"
"  +  413"
*/

// 获取第一个可以表示整数的子串
bool GetAIntegerFromString(char *dest, const char *source)
{
    int length = strlen(source);
    int indexSource = 0;
    int indexDest = 0;

    bool flagOperator = false;

    // !题目要求数字前面只能是+\-和前导空格："words and 987" 👈这个要求返回0
    // 为了应对这种情况，如果在存数之前发现了正负号和数字以外的字符，返回 false

    // 根据题目的描述，应该不存在 "  ---123" 或者 "-123-11..."、"-"这样的式子，所以很多判断都简化了
    //!事实证明我想多了，有这种测试用例："+-12"
    // 为了应对这种情况，如果在存数之前出现了第二次+/-，就返回false

    // 遍历整个字符串
    while (source[indexSource] != '\0')
    {
        if (source[indexSource] == ' ')
        {
            // 如果是 ' '什么也不做
        }
        else if (source[indexSource] == '-' || source[indexSource] == '+')
        {
            // 早知道还是把复制过来的函数好好改改了，属实是找死，条件写成这样都变成暴力破解测试用例了

            // 正负号后面不是数字，返回 false
            if (source[indexSource + 1] < '0' || source[indexSource + 1] > '9')
                return false;

            // 又发现了正负号，肯定是出错了，返回false
            if (flagOperator == true)
            {
                return false;
            }
            // 如果是负号，记下来（'+'不记录，因为第6题写的函数直接抛弃了'+'）
            if (source[indexSource] == '-')
                dest[indexDest++] = source[indexSource];

            // 见到符号了
            flagOperator = true;
        }
        else if (source[indexSource] >= '0' && source[indexSource] <= '9')
        {
            // 如果是数字，记下来
            dest[indexDest++] = source[indexSource];

            // 如果下一个不是数字，那就已经遍历完了，可以返回了
            if (source[indexSource + 1] < '0' || source[indexSource + 1] > '9')
            {
                return true;
            }
        }
        else if (indexDest == 0)
        {
            // 也不是空格，也不是数字，也不是正负数，也没有发现数字，说明出现了奇怪的前导字符，识别失败，返回false
            return false;
        }

        // 继续往下遍历
        indexSource++;
    }

    // 正常遍历结束，返回true
    return true;
}

// 判断给定的这个字符串代表的数字有没有溢出
bool isOverflow(const char *num)
{
    // 数字至少有一位，不需要判断是不是空串

    // !第7题给的是int，但第8题给的是char*，长度和第7题不一样，判断条件要补充
    // 如果是负数，数字部分超过10位||如果是正数，数字部分超过10位
    if (num[0] == '-' && strlen(num) > 11 || num[0] != '-' && strlen(num) > 10)
        return true;

    // 如果是负数，而且长度等于12（这个长度说的是字符串总长，包括\0）
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

// 剔除前导0
void CutPeriodZero(char *num)
{
    int index = 0;
    // 如果有符号，就跳一位（实际上不会有正号，正号在转换的时候被丢了）
    if (num[0] == '-' || num[0] == '+')
    {
        index = 1;
    }

    int count = 0;
    // 数一下有几个0，后面统一覆盖
    while (num[index++] == '0')
    {
        count++;
    }

    /**
     * 解释一下👇
     *
     * -000123
     * index=1,count=4
     *
     * 000123
     * index=0,count=3
     */

    // 有符号就跳一格
    if (num[0] == '-' || num[0] == '+')
    {
        index = 1;
        count++;
    }
    else
    {
        index = 0;
    }

    // 开始覆盖（这个循环的思路来自 strcpy 的实现）
    while ((num[index++] = num[count++]) != '\0')
        ;
}

int myAtoi(char *s)
{
    // 字符串转数字啊，老活了
    // 第7题写过一个判断是否溢出的函数和一个字符串转整数的函数，可以直接拿来用
    // 所以这里要做的就是把字符串里数字的部分读出来就行了

    // 空字符串,直接返回
    if (strlen(s) == 0)
        return 0;

    // 可能会有一大串的前导0，所以长一点 (本来 12位刚好够，10位数字，1位符号)
    char numString[256] = "0";

    // 截取数字部分，如果出错了，就直接返回0
    if (GetAIntegerFromString(numString, s) == false)
        return 0;

    // 去一下前导0
    CutPeriodZero(numString);

    // 如果溢出就不用转换成整数了
    if (isOverflow(numString))
    {
        if (numString[0] == '-')
            return -2147483648;
        else
            return 2147483647;
    }
    // 没有溢出就正常转换
    else
    {
        return stringToInt(numString);
    }
}
// @lc code=end
