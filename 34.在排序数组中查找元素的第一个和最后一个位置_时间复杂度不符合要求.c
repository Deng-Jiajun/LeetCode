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
    /* 这里的复杂度是 O(m)（m是目标值的数量） ，显然不满足 O(log n) */ 
    if (targetIndex != -1)
    {
        // 虽然不知道总共个目标值，但是这些值肯定在 [left,right] 里

        // 先赋值一下
        result[0] = targetIndex; // 开始位置
        result[1] = targetIndex; // 结束位置

        // 左探
        while (result[0] != left)
        {
            // reuslt[0] - 1 不会溢出，因为 left 最小是 0，而 reuslt[0] != left
            if (nums[result[0] - 1] == target)
            {
                // 如果左边的值也是目标值，就左移一位
                result[0]--;
            }
            else
            {
                // 不等于就可以退出循环了
                break;
            }
        }

        // 右探
        while (result[1] != right)
        {
            // result[1] + 1 不会溢出，因为 result[1] != right
            if (nums[result[1] + 1] == target)
            {
                // 如果右边的值也是目标值，就右移一位
                result[1]++;
            }
            else
            {
                // 不等于就可以退出循环了
                break;
            }
        }
    }

    return result;
}
// @lc code=end
