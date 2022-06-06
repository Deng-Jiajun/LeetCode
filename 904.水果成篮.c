/*
 * @lc app=leetcode.cn id=904 lang=c
 *
 * [904] 水果成篮
 *
 * https://leetcode.cn/problems/fruit-into-baskets/description/
 *
 * algorithms
 * Medium (43.89%)
 * Likes:    223
 * Dislikes: 0
 * Total Accepted:    50.6K
 * Total Submissions: 115.2K
 * Testcase Example:  '[1,2,1]'
 *
 * 你正在探访一家农场，农场从左到右种植了一排果树。这些树用一个整数数组 fruits 表示，其中 fruits[i] 是第 i 棵树上的水果 种类 。
 *
 * 你想要尽可能多地收集水果。然而，农场的主人设定了一些严格的规矩，你必须按照要求采摘水果：
 *
 *
 * 你只有 两个 篮子，并且每个篮子只能装 单一类型 的水果。每个篮子能够装的水果总量没有限制。
 * 你可以选择任意一棵树开始采摘，你必须从 每棵 树（包括开始采摘的树）上 恰好摘一个水果
 * 。采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
 * 一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
 *
 *
 * 给你一个整数数组 fruits ，返回你可以收集的水果的 最大 数目。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：fruits = [1,2,1]
 * 输出：3
 * 解释：可以采摘全部 3 棵树。
 *
 *
 * 示例 2：
 *
 *
 * 输入：fruits = [0,1,2,2]
 * 输出：3
 * 解释：可以采摘 [1,2,2] 这三棵树。
 * 如果从第一棵树开始采摘，则只能采摘 [0,1] 这两棵树。
 *
 *
 * 示例 3：
 *
 *
 * 输入：fruits = [1,2,3,2,2]
 * 输出：4
 * 解释：可以采摘 [2,3,2,2] 这四棵树。
 * 如果从第一棵树开始采摘，则只能采摘 [1,2] 这两棵树。
 *
 *
 * 示例 4：
 *
 *
 * 输入：fruits = [3,3,3,1,2,1,1,2,3,3,4]
 * 输出：5
 * 解释：可以采摘 [1,2,1,1,2] 这五棵树。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= fruits.length <= 10^5
 * 0 <= fruits[i] < fruits.length
 *
 *
 */

// @lc code=start

int totalFruit(int *fruits, int fruitsSize)
{
    /* 需要明确一点，最终找到的那个区间，里面只会有最多两种水果，所以维持一个至多两种水果类型的区间即可 */
    int left = 0;
    int right = 0;
    int max = 0;           // 区间内水果最大数量
    int type_fruits = 1;   // 区间内的）水果种类数量，至少有 1 种
    int type1 = fruits[0]; // （区间内的）第一种水果类型
    int type2 = fruits[0]; // （区间内的）第二种水果类型

    /* 每次迭代都要更新区间的左右边界，使区间内始终维持两种水果类型 */
    while (1)
    {
        /* [left, right] 区间左闭右闭 */
        /* 先让右边界右移 */
        while (right < fruitsSize - 1)
        {
            /* 如果不是新的水果类型，直接纳入范围 */
            if (fruits[right + 1] == type1 || fruits[right + 1] == type2)
            {
                right++; // 右边界右移
            }
            else /* 如果是新的水果类型 */
            {
                /* 而当前区间内只有一种水果，那就可以纳入范围 */
                if (type_fruits == 1)
                {
                    right++;               // 右边界右移
                    type_fruits = 2;       // 更新水果种类数量
                    type2 = fruits[right]; // 新的水果种类肯定是第二种
                }
                else /* 如果区间内已经有两种水果，就跳出循环 */
                {
                    break;
                }
            }
            // printf("left: %d, right: %d, type1: %d, type2: %d, type_fruits: %d\n", left, right, type1, type2, type_fruits);
        } /* 跳出循环则得到了一个新的区间，里面至多有两种水果 */

        /* 更新最大值 */
        max = max > right - left + 1 ? max : right - left + 1;

        /* 如果遍历完毕，那就跳出循环 */
        if (right == fruitsSize - 1)
        {
            break;
        }
        else /* 否则就让左边界右移，直到区间内只剩下右边界上的那种水果 */
        {
            /* 直接从右边界往左找第一个不为 fruits[right] 的水果 */
            left = right - 1;
            while (left >= 0 && fruits[left] == fruits[right])
            {
                left--;
            } /* 退出循环时，left右边全是 fruits[right] */

            left++;                // 然后再右移一位，则区间内只剩下 fruits[right]
            type_fruits = 1;       // 更新水果种类数量
            type1 = fruits[right]; // 更新水果种类
            type2 = fruits[right]; // 更新水果种类
        }
    }
    return max;
}
// @lc code=end
