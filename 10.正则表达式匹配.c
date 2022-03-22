/*
 * @lc app=leetcode.cn id=10 lang=c
 *
 * [10] 正则表达式匹配
 *
 * https://leetcode-cn.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (31.63%)
 * Likes:    2823
 * Dislikes: 0
 * Total Accepted:    252K
 * Total Submissions: 797.8K
 * Testcase Example:  '"aa"\n"a"'
 *
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
 *
 *
 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 *
 *
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "aa", p = "a"
 * 输出：false
 * 解释："a" 无法匹配 "aa" 整个字符串。
 *
 *
 * 示例 2:
 *
 *
 * 输入：s = "aa", p = "a*"
 * 输出：true
 * 解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "ab", p = ".*"
 * 输出：true
 * 解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 20
 * 1 <= p.length <= 30
 * s 只包含从 a-z 的小写字母。
 * p 只包含从 a-z 的小写字母，以及字符 . 和 *。
 * 保证每次出现字符 * 时，前面都匹配到有效的字符
 *
 *
 */

// @lc code=start

bool isMatch(char *s, char *p)
{
    
    // 首先如果两个字符串相等，肯定匹配成功，如果表达式是「.*」也肯定匹配成功

    if (strcmp(s, p) == 0 || strcmp(p, ".*") == 0)
        return true;

    // 找一下表达式里有没有「*」
    int indexOfStar = -1;

    for (int i = 0; p[i] != '\0'; i++)
    {
        if (p[i] == '*')
        {
            indexOfStar = i;
            break;
        }
    }

    // 如果字符串里没有「*」
    if (indexOfStar == -1)
    {

        // 如果两个字符串 不等长，那么没有匹配成功的可能性
        if (strlen(s) != strlen(p))
        {
            return false;
        }
        // 如果两个字符串 等长，那就看除了「.」之外的每一位字符是不是完全一样
        else
        {
            for (int i = 0; p[i] != '\0'; i++)
            {
                // 等长字符串，同时推进没有溢出的问题
                // 如果某一位不相等，而且表达式里也不是「.」，自然匹配失败
                if (s[i] != p[i] && p[i] != '.')
                {
                    return false;
                }
            }
            // 如果通过了循环，那就匹配成功了（表达式和字符串等长，有部分位是「.」)
            return true;
        }
    }
    // 如果字符串里有「*」
    else
    {
        /**
         * 很好，我不会了
         * 思路总结一下
         *
         * 首先找到第一个* 的位置，看一下它的前面一个是什么符号
         * 两个字符串都从0开始对比，第一个不同的符号是什么？
         *
         * case1:
         *  abcde
         *  k*……
         *  第一个不同的是a，和k没关系，但是因为k* 前面没有子串，而k可以是0个，
         *  所以继续匹配，index_p=index_p+2; index_s不变，还是0
         *
         * case2:
         *  abcde
         *  ak*……
         *  第一个不同的是b，和k没关系，但是因为k* 前面的子串成功了，
         *  而k可以是0个，所以继续匹配， index_s=1,index_p=1; index_p=index_p+2;
         *
         * case3:
         *  abcde
         *  ek*……
         *  匹配失败，false
         *
         * 3个case的总结：匹配 k* 前面的部分，如果匹配成功，就没事，失败就完蛋
         *
         * 很好，总结不下去了，自闭了
         *
         *
         * 再写点……
         * 首先很明确的一点，要根据 [a-z]* 把表达式做切割
         * 一块块地去和字符串做匹配
         * ……算了，太难了
         *
         *
         */


    }
}
// @lc code=end
