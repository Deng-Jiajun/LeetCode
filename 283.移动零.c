/*
 * @lc app=leetcode.cn id=283 lang=c
 *
 * [283] 移动零
 *
 * https://leetcode-cn.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (64.01%)
 * Likes:    1512
 * Dislikes: 0
 * Total Accepted:    682.3K
 * Total Submissions: 1.1M
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 *
 * 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: nums = [0,1,0,3,12]
 * 输出: [1,3,12,0,0]
 *
 *
 * 示例 2:
 *
 *
 * 输入: nums = [0]
 * 输出: [0]
 *
 *
 *
 * 提示:
 *
 *
 *
 * 1 <= nums.length <= 10^4
 * -2^31 <= nums[i] <= 2^31 - 1
 *
 *
 *
 *
 * 进阶：你能尽量减少完成的操作次数吗？
 *
 */

// @lc code=start

void moveZeroes(int *nums, int numsSize)
{

    /**
     * 这题和 27 题比较类似，也是删除目标元素
     * 只是再多做一步，在末尾后面补 0，判断条件比 26 题简单
     *
     * 0 的数量 n = 原数组长度 - 新数组长度
     * 从 nums[numsSize-1] 开始往前写 n 个 0 就行了
     */

    int j = 0; // 新数组目前遍历到的位置，同时也是新数组的长度

    // 遍历整个数组，如果不等于 0，就采用
    for (int i = 0; i != numsSize; i++)
    {
        if (nums[i] != 0)
            nums[j++] = nums[i];
    }

    // 从 nums[numsSize-1] 开始写 0
    for (int i = 0; i != numsSize - j; i++)
    {
        nums[numsSize - 1 - i] = 0;
    }
}
// @lc code=end
