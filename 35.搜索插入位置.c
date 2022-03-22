/*
 * @lc app=leetcode.cn id=35 lang=c
 *
 * [35] 搜索插入位置
 *
 * https://leetcode-cn.com/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (45.59%)
 * Likes:    1424
 * Dislikes: 0
 * Total Accepted:    712.1K
 * Total Submissions: 1.6M
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 *
 * 请必须使用时间复杂度为 O(log n) 的算法。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: nums = [1,3,5,6], target = 5
 * 输出: 2
 *
 *
 * 示例 2:
 *
 *
 * 输入: nums = [1,3,5,6], target = 2
 * 输出: 1
 *
 *
 * 示例 3:
 *
 *
 * 输入: nums = [1,3,5,6], target = 7
 * 输出: 4
 *
 *
 * 示例 4:
 *
 *
 * 输入: nums = [1,3,5,6], target = 0
 * 输出: 0
 *
 *
 * 示例 5:
 *
 *
 * 输入: nums = [1], target = 0
 * 输出: 0
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1
 * -10^4
 * nums 为无重复元素的升序排列数组
 * -10^4
 *
 *
 */

// @lc code=start

/**
 * 这题和 704 一样，二分查找，区别在于没找到的时候要返回按序插入的位置
 */
int searchInsert(int *nums, int numsSize, int target)
{

    // 全闭区间
    int left = 0;
    int right = numsSize - 1;
    int middle;

    // 闭区间，相等的时候有意义，要查一下
    while (left <= right)
    {
        middle = (left + right) / 2;

        // 找到了，返回位置
        if (target == nums[middle])
        {
            return middle;
        }
        // 目标值更小，找左边那半
        else if (target < nums[middle])
        {
            right = middle - 1;
        }
        // 目标值更大，找右边那半
        else if (target > nums[middle])
        {
            left = middle + 1;
        }
    }

    // 所以如果没找到，这个位置这么确定呢？
    /*
    1. 头部插入（0）
    这种情况位置 = middle（也就是**left**，因为这个值太小，left没变过，一直是0）

    2. 中间插入（numSize)
    这种情况，如果 target < nums[middle]，那位置就是middle（也就是**left**，因为要往左边找）；如果 target > nums[middle]，那位置就是middle+1（也就是**left**，因为要往右边找）

    3. 尾部插入（middle?）
    这种情况位置 = middle+1(也就是**left**，因为太大，所以要往右)
    */
    // 结论是：全都返回left就行了
    return left;
}
// @lc code=end
