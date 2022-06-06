/*
 * @lc app=leetcode.cn id=209 lang=c
 *
 * [209] 长度最小的子数组
 *
 * https://leetcode-cn.com/problems/minimum-size-subarray-sum/description/
 *
 * algorithms
 * Medium (48.22%)
 * Likes:    1191
 * Dislikes: 0
 * Total Accepted:    342K
 * Total Submissions: 701.3K
 * Testcase Example:  '7\n[2,3,1,2,4,3]'
 *
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 *
 * 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr]
 * ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：target = 7, nums = [2,3,1,2,4,3]
 * 输出：2
 * 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
 *
 *
 * 示例 2：
 *
 *
 * 输入：target = 4, nums = [1,4,4]
 * 输出：1
 *
 *
 * 示例 3：
 *
 *
 * 输入：target = 11, nums = [1,1,1,1,1,1,1,1]
 * 输出：0
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * 1
 * 1
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。
 *
 *
 */

// @lc code=start

/**
 * @brief 寻找以当前下标开始的连续子数组，使其和大于等于 target
 *
 * @param target 目标和
 * @param nums 数组指针
 * @param numsSize 数组大小
 * @param index 当前下标
 * @return int 返回子数组长度（没有则返回 -1）
 */
int __minSubArrayLen(int target, int *nums, int numsSize, int index)
{
    /* 从当前下标开始求和，直到sum >= target，返回子数组长度 */
    int sum = 0;
    for (int i = index; i < numsSize; i++)
    {
        sum += nums[i];
        // printf("index: %d, i: %d, sum: %d (len: %d)\n", index, i, sum, i - index + 1);
        if (sum >= target)
        {
            return i - index + 1;
        }
    }

    /* 若走出循环，则返回 -1 */
    return -1;
}

int minSubArrayLen(int target, int *nums, int numsSize)
{
    /* 暴力解法，一位位迭代，找以每一个下标开始的子数组长度 */
    int min_len = numsSize + 1; // 最小长度
    int index = 0;              // 当前迭代的下标
    int temp_len = 0;           // 当前迭代得到的子数组长度
    
    while (index < numsSize)
    {
        temp_len = __minSubArrayLen(target, nums, numsSize, index);
        if (temp_len == -1) // 如果找不到，则退出（后面不会再有更小的子数组了）
            break;
        else if (temp_len < min_len)
            min_len = temp_len;
        // printf("min_len = %d\n", min_len);
        index++;
    }
    if (min_len == numsSize + 1)
        return 0;
    else
        return min_len;
}
// @lc code=end
