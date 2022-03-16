/*
 * @lc app=leetcode.cn id=6 lang=c
 *
 * [6] Z 字形变换
 *
 * https://leetcode-cn.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (51.93%)
 * Likes:    1608
 * Dislikes: 0
 * Total Accepted:    401.6K
 * Total Submissions: 773.5K
 * Testcase Example:  '"PAYPALISHIRING"\n3'
 *
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
 *
 * 比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
 *
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * 之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
 *
 * 请你实现这个将字符串进行指定行数变换的函数：
 *
 *
 * string convert(string s, int numRows);
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "PAYPALISHIRING", numRows = 3
 * 输出："PAHNAPLSIIGYIR"
 *
 * 示例 2：
 *
 *
 * 输入：s = "PAYPALISHIRING", numRows = 4
 * 输出："PINALSIGYAHRPI"
 * 解释：
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "A", numRows = 1
 * 输出："A"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * s 由英文字母（小写和大写）、',' 和 '.' 组成
 * 1
 *
 *
 */

// @lc code=start

char *convert(char *s, int numRows)
{
    /**
     * 找一下规律
     * ↓↗↓↗↓↗
     *
     * numRows      ：上下的深度
     * numRows-2    ：斜向的深度（>=0)
     *
     * numRows=1：0, 1, 2, 3, 4 ……
     * numRows=2：0, 2, 4, 6,……
     *            1，3, 5, 7,……
     *
     * numRows=3：0,  , 4,  ,  8,   ,  12
     *            1, 3, 5, 7,  9, 11,  13
     *            2,  , 6,  , 10,   ,  14
     *
     * numRows=4：0,  ,  , 6,   ,   , 12
     *            1,  , 5, 7,   , 11, 13
     *            2, 4,  , 8, 10,   , 14
     *            3,  ,  , 9,   ,   , 15
     *
     * 例一： numRows=3  period = 4
     * 下标 0 1 2 3 | 4 5 6 7 | 8 9 10 11 | 12 13 14 15 | 16
     * 行数 0 1 2 1 | 0 1 2 1 | 0 1  2  1 |  0  1  2  1 | 0  1  2  1
     *
     * 例二： numRows=4  period = 6
     * 下标 0 1 2 3 4 5 | 6 7 8 9 10 11 | 12 13 14 15 16
     * 行数 0 1 2 3 2 1 | 0 1 2 3  2  1 |  0  1  2  3  2  1 |
     *
     * 结论：每个字符所处行数存在周期
     *
     * 周期 period = numRows*2-2;
     *
     * 一个周期内，每行至多填入两个字符
     * 每行子串长度设为：(length/period)*2 + 2 (懒得做上取整，直接多给两格)
     */

    // 如果行数是0直接返回s
    if (numRows == 1)
        return s;

    // 源字符串长度
    int sourceStringLength = strlen(s);

    // 周期
    int period = numRows * 2 - 2;

    // 每行子串分配长度
    int subStringLength = (sourceStringLength / period) * 2 + 2;

    // 创建子串并初始化
    char **line;
    line = (char **)malloc((numRows) * sizeof(char *));
    for (int i = 0; i < numRows; i++)
    {
        line[i] = (char *)malloc((subStringLength + 1) * sizeof(char));
        memset(line[i], '\0', (subStringLength + 1) * sizeof(char));
    }
    // 创建待返回字符串并初始化
    char *returnString;
    returnString = (char *)malloc((sourceStringLength + 1) * sizeof(char));
    memset(returnString, '\0', (sourceStringLength + 1) * sizeof(char));

    // 当前遍历的字符位于本周期中的下标
    int indexOfCurrentPeriod;
    // 当前遍历到的字符应该在第几行
    int currentLine;

    // 因为懒得记录每一行的长度，建立一个临时字符串，长度为2（第二位是 '\0'），用于记录每次遍历到的字符，通过 strcat 拼接到子串行尾
    char tempString[2] = {'\0', '\0'};

    /*
     ps：
     这里一个可以选择直接以周期为单位进行遍历，因为每个周期长度一致，只要对最后一个周期做一下判断就行了（加个 count，判断是不是超了）
     这种方式可以这么处理：
     第一段：0,1,2 … numRows-3, numRows-2, numRows-1 👈最多到 numRows-1
     第二段：      → numRows-2,numRows-3, …,1 👈最多只能到1，到0是下一个周期
    */

    // 遍历源字符串
    for (int i = 0; i < sourceStringLength; i++)
    {
        // 把当前字符存入 tempString
        tempString[0] = s[i];

        // 当前字符下标对周期宽度取余，得到其位于周期内的下标
        indexOfCurrentPeriod = i % period;

        // 周期内下标小于行数，处于↓
        if (indexOfCurrentPeriod < numRows)
        {
            currentLine = indexOfCurrentPeriod;
        }
        else
        {
            // 周期内下标大于等于行数，处于↗
            // 周期宽度减周期内下标，宽度不变，随着下标增大，当前所在行减小
            currentLine = period - indexOfCurrentPeriod;
        }
        // 👇这个三目运算和上面的IF ELSE 完全等价
        // currentRow = ((i % period) < numRows) ? (i % period) : (period - (i % period));

        // 现在拿到了当前字符应该在哪一行，把它拼接到那一行的行尾
        strcat(line[currentLine], tempString);
    }

    // 子串合并到返回字符串
    for (int i = 0; i < numRows; i++)
    {
        strcat(returnString, line[i]);
    }

    return returnString;
}
// @lc code=end
