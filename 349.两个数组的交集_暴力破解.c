/*
 * @lc app=leetcode.cn id=349 lang=c
 *
 * [349] 两个数组的交集
 *
 * https://leetcode.cn/problems/intersection-of-two-arrays/description/
 *
 * algorithms
 * Easy (74.19%)
 * Likes:    556
 * Dislikes: 0
 * Total Accepted:    307.4K
 * Total Submissions: 414.1K
 * Testcase Example:  '[1,2,2,1]\n[2,2]'
 *
 * 给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,2,2,1], nums2 = [2,2]
 * 输出：[2]
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * 输出：[9,4]
 * 解释：[4,9] 也是可通过的
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums1.length, nums2.length <= 1000
 * 0 <= nums1[i], nums2[i] <= 1000
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *intersection(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    /* 二者的交集，最大也就是更短的那个数组大小 */
    int *result = (int *)malloc(sizeof(int) * (nums1Size));
    *returnSize = 0;
    for (int i = 0; i != nums1Size; i++)
    {
        /* 如果结果中有这个数，则跳过 */
        for (int k = 0; k != *returnSize; k++)
        {
            if (result[k] == nums1[i])
            {
                goto next;
            }
        }

        /* 没有的话，就看这个数在不在第二个数组中 */
        for (int j = 0; j != nums2Size; j++)
        {
            if (nums1[i] == nums2[j])
            {
                result[*returnSize] = nums1[i];
                (*returnSize)++;
                break;
            }
        }
    next:;
    }

    return result;
}
// @lc code=end
