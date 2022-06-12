/*
 * @lc app=leetcode.cn id=350 lang=c
 *
 * [350] 两个数组的交集 II
 *
 * https://leetcode.cn/problems/intersection-of-two-arrays-ii/description/
 *
 * algorithms
 * Easy (56.23%)
 * Likes:    768
 * Dislikes: 0
 * Total Accepted:    362.7K
 * Total Submissions: 644.8K
 * Testcase Example:  '[1,2,2,1]\n[2,2]'
 *
 * 给你两个整数数组 nums1 和 nums2
 * ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,2,2,1], nums2 = [2,2]
 * 输出：[2,2]
 *
 *
 * 示例 2:
 *
 *
 * 输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * 输出：[4,9]
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
 *
 *
 * 进阶：
 *
 *
 * 如果给定的数组已经排好序呢？你将如何优化你的算法？
 * 如果 nums1 的大小比 nums2 小，哪种方法更优？
 * 如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    int record1[1001] = {0};
    int record2[1001] = {0};
    int *result = (int *)malloc(sizeof(int) * nums1Size);
    *returnSize = 0;

    /* 分别计算两个数组中每个数字的出现次数 */
    for (int i = 0; i < nums1Size; i++)
    {
        record1[nums1[i]]++;
    }
    for (int i = 0; i < nums2Size; i++)
    {
        record2[nums2[i]]++;
    }

    /* 然后逐位比较，选取二者中更小的值个数的 i，写入结果数组 */
    int count;
    for (int i = 0; i < 1001; i++)
    {
        /* 选取二者的更小值 */
        count = record1[i] > record2[i] ? record2[i] : record1[i];

        /* 输出 count 个 i 到结果数组 */
        for (int j = 0; j < count; j++)
        {
            result[*returnSize] = i;
            (*returnSize)++;
        }
    }

    return result;
}
// @lc code=end
