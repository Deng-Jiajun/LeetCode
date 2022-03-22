/*
 * @lc app=leetcode.cn id=704 lang=c
 *
 * [704] 二分查找
 *
 * https://leetcode-cn.com/problems/binary-search/description/
 *
 * algorithms
 * Easy (54.44%)
 * Likes:    717
 * Dislikes: 0
 * Total Accepted:    498.5K
 * Total Submissions: 917.8K
 * Testcase Example:  '[-1,0,3,5,9,12]\n9'
 *
 * 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的
 * target，如果目标值存在返回下标，否则返回 -1。
 *
 *
 * 示例 1:
 *
 * 输入: nums = [-1,0,3,5,9,12], target = 9
 * 输出: 4
 * 解释: 9 出现在 nums 中并且下标为 4
 *
 *
 * 示例 2:
 *
 * 输入: nums = [-1,0,3,5,9,12], target = 2
 * 输出: -1
 * 解释: 2 不存在 nums 中因此返回 -1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 你可以假设 nums 中的所有元素是不重复的。
 * n 将在 [1, 10000]之间。
 * nums 的每个元素都将在 [-9999, 9999]之间。
 *
 *
 */

// @lc code=start

int search(int *nums, int numsSize, int target)
{

    // 这里选择全闭区间

    int left = 0;
    int right = numsSize - 1; // 全闭，所以 right 是 size-1
    int middle;

    // 确定是全闭区间，那么左右值相等的时候，也要判断一下
    while (left <= right)
    {
        // middle 的值不需要考虑上下取整的问题，这里只是要在 left 和 right 之间找一个位置而已，是往左还是往右一位都可以（区别只在于临界情况下它是等于 left 还是 right，这里选择了 left）
        middle = (left + right) / 2;

        // 找到了，就返回
        if (target == nums[middle])
        {
            return middle;
        }
        // 目标值比 middle 的值小，往左边找
        else if (target < nums[middle])
        {
            // middle 的值已经不符合了，所以把它排除在区间外
            right = middle - 1;
        }
        // 目标值比 middle 的值大，往右边找
        else if (target > nums[middle])
        {
            // middle 的值已经不符合了，所以把它排除在区间外
            left = middle + 1;
        }
    }

    // 没找到，返回 -1
    return -1;
}
// @lc code=end
