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

int minSubArrayLen(int target, int *nums, int numsSize)
{
    /* 滑动窗口法 */
    int left = 0;
    int right = 0;
    int sum = 0;
    int min_len = numsSize + 1;
    while (1)
    {
        /* 窗口可以分为两个阶段
        1. 右边界右移，直到 sum >= target
        2. 左边界右移，直到 sum < target
        移动后判定是否更新 min_len
        */

        /* [left,right) 左闭右开 */

        /* 右边界右移（前提条件：未遍历完毕、子数组和 < target） */
        while (right < numsSize && sum < target)
        {
            sum += nums[right++];
        } /* 出循环的两个可能：right==numsSize（遍历完毕） 或 sum>=target（新范围确定） */

        if (sum >= target) /* 如果构成了新范围，才有判定min_len和左边界右移的意义 */
        {
            /* 判定 min_len 是否需要更新 */
            if (right - left < min_len)
            {
                min_len = right - left;
            }

            /* 左边界右移(直到 sum < target) */
            while (sum >= target && left < right)
            {
                sum -= nums[left++];
            }

            /* 判定 min_len 是否需要更新(这里需要+1，因为现在 sum<target，但是左边界右移前是 sum >= target) */
            if (right - left + 1 < min_len)
            {
                min_len = right - left + 1;
            }
        }
        else /* 否则就是遍历完毕，跳出循环 */
        {
            break;
        }
    }
    return min_len == numsSize + 1 ? 0 : min_len;
}
// @lc code=end
