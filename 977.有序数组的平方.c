/*
 * @lc app=leetcode.cn id=977 lang=c
 *
 * [977] 有序数组的平方
 *
 * https://leetcode-cn.com/problems/squares-of-a-sorted-array/description/
 *
 * algorithms
 * Easy (69.37%)
 * Likes:    477
 * Dislikes: 0
 * Total Accepted:    291.4K
 * Total Submissions: 422.2K
 * Testcase Example:  '[-4,-1,0,3,10]'
 *
 * 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。
 *
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [-4,-1,0,3,10]
 * 输出：[0,1,9,16,100]
 * 解释：平方后，数组变为 [16,1,0,9,100]
 * 排序后，数组变为 [0,1,9,16,100]
 *
 * 示例 2：
 *
 *
 * 输入：nums = [-7,-3,2,3,11]
 * 输出：[4,9,9,49,121]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 10^4
 * -10^4
 * nums 已按 非递减顺序 排序
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 请你设计时间复杂度为 O(n) 的算法解决本问题
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *nums, int numsSize, int *returnSize)
{

    // 建立返回数组
    int *result = (int *)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize; // 搞不懂为什么好多题目都要这个

    // 左右指针
    int left = 0;
    int right = numsSize - 1;

    // 写入的位置（从后往前）
    int index = numsSize - 1;

    while (left < right)
    {
        // 选大的
        if (nums[left] * nums[left] > nums[right] * nums[right])
        {
            result[index--] = nums[left] * nums[left];
            left++;
        }
        else
        {
            result[index--] = nums[right] * nums[right];
            right--;
        }
    }

    // 最后剩一个，手动写进去（可以在循环里做，但是直接写更快）
    result[0] = nums[left] * nums[left];
    return result;
}
// @lc code=end
