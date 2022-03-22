/*
 * @lc app=leetcode.cn id=34 lang=c
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 *
 * https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 *
 * algorithms
 * Medium (42.29%)
 * Likes:    1549
 * Dislikes: 0
 * Total Accepted:    473.6K
 * Total Submissions: 1.1M
 * Testcase Example:  '[5,7,7,8,8,10]\n8'
 *
 * 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
 *
 * 如果数组中不存在目标值 target，返回 [-1, -1]。
 *
 * 进阶：
 *
 *
 * 你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [5,7,7,8,8,10], target = 8
 * 输出：[3,4]
 *
 * 示例 2：
 *
 *
 * 输入：nums = [5,7,7,8,8,10], target = 6
 * 输出：[-1,-1]
 *
 * 示例 3：
 *
 *
 * 输入：nums = [], target = 0
 * 输出：[-1,-1]
 *
 *
 *
 * 提示：
 *
 *
 * 0
 * -10^9 
 * nums 是一个非递减数组
 * -10^9 
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int FindFirst(int *nums, int left, int right, int target)
{
    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;
        // 当前值等于 target，需要判断前面还有有没有target
        if (target == nums[middle])
        {
            // 如果 middle 已经是 left，或者前一个数不是 target，则左边界已明确
            // 👇注意这个短路逻辑，如果 left 是 0，middle-1会溢出，所以要先判断
            if (middle == left || nums[middle - 1] != target)
            {
                return middle;
            }
            else // nums[middle - 1] == target
            {
                // 前一个数还是 target，左边界不明确，继续循环
                right = middle - 1;
            }
        }
        else if (target < nums[middle])
        {
            // 当前值比目标值大，往左边找
            right = middle - 1;
        }
        else if (target > nums[middle])
        {
            // 当前值比目标值大，往右边找
            left = middle + 1;
        }
    }
    return -1;
}

int FindLast(int *nums, int left, int right, int target)
{
    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;
        // 当前值等于 target，需要判断前面还有有没有target
        if (target == nums[middle])
        {
            // 如果 middle 已经是 right，或者后一个数不是 target，则右边界已明确
            // 👇注意这个短路逻辑，一定要先判断 middle 是不是right，不然会溢出
            if (middle == right || nums[middle + 1] != target)
            {
                return middle;
            }
            else // nums[middle + 1] == target
            {
                // 后一个数还是 target，右边界不明确，继续循环
                left = middle + 1;
            }
        }
        else if (target < nums[middle])
        {
            // 当前值比目标值大，往左边找
            right = middle - 1;
        }
        else if (target > nums[middle])
        {
            // 当前值比目标值大，往右边找
            left = middle + 1;
        }
    }
    return -1;
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
    // 创建返回数组
    int *result = (int *)malloc(sizeof(int) * 2);
    // 初始化
    result[0] = result[1] = -1;

    *returnSize = 2; // 不然呢？

    /**
     * 思路：
     * 用二分找到目标值，没有就直接返回 result（已经初始化为 [-1，-1] 了）
     *                   找得到，往左右两边探就是了
     */

    // 左闭右闭
    int left = 0;
    int right = numsSize - 1;
    int middle;
    int targetIndex = -1;

    while (left <= right)
    {
        middle = (left + right) / 2;
        if (target == nums[middle])
        {
            // 找到了就可以开始探边界，直接在这里写太乱，先跳出再说
            targetIndex = middle;
            break;
        }
        else if (target < nums[middle])
        {
            // 当前值比目标值大，往左边找
            right = middle - 1;
        }
        else if (target > nums[middle])
        {
            // 当前值比目标值大，往右边找
            left = middle + 1;
        }
    }

    // 探边界
    if (targetIndex != -1)
    {
        // 虽然不知道总共个目标值，但是这些值肯定在 [left,right] 里
        // 分别二分查找左右半边（不需要考虑溢出的问题，left>right 会返回 -1）
        if (FindFirst(nums, left, targetIndex - 1, target) != -1)
        {
            result[0] = FindFirst(nums, left, targetIndex - 1, target);
        }
        else
        {
            result[0] = targetIndex;
        }

        if (FindLast(nums, targetIndex + 1, right, target) != -1)
        {
            result[1] = FindLast(nums, targetIndex + 1, right, target);
        }
        else
        {
            result[1] = targetIndex;
        }
    }

    return result;
}
// @lc code=end
