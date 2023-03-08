/*
 * @lc app=leetcode.cn id=239 lang=c
 *
 * [239] 滑动窗口最大值
 *
 * https://leetcode.cn/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (50.03%)
 * Likes:    1903
 * Dislikes: 0
 * Total Accepted:    365.5K
 * Total Submissions: 730.6K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
 * 个数字。滑动窗口每次只向右移动一位。
 *
 * 返回 滑动窗口中的最大值 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
 * 输出：[3,3,5,5,6,7]
 * 解释：
 * 滑动窗口的位置                最大值
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 * ⁠1 [3  -1  -3] 5  3  6  7       3
 * ⁠1  3 [-1  -3  5] 3  6  7       5
 * ⁠1  3  -1 [-3  5  3] 6  7       5
 * ⁠1  3  -1  -3 [5  3  6] 7       6
 * ⁠1  3  -1  -3  5 [3  6  7]      7
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1], k = 1
 * 输出：[1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{
    if (k == 0) // 窗口大小为 0，直接返回空数组
    {
        *returnSize = 0;
        return NULL;
    }
    if (k == 1) // 窗口大小为 1，直接返回数组本身
    {
        *returnSize = numsSize;
        return nums;
    }

    /* 建立一个数组，用来放队列（左大右小，单调递减） */
    int *queue = (int *)malloc(sizeof(int) * numsSize); // 左闭右闭
    // 👆存放的是在原数组的下标，而不是数组元素

    /* 建立一个数组，用来放返回的数组 */
    int *ret = (int *)malloc(sizeof(int) * (numsSize - k + 1));
    *returnSize = numsSize - k + 1;
    int ret_index = 0; // 返回数组的下标

    int left = 0;  // 队列左边界
    int right = 0; // 队列右边界
    int index = 0; // 遍历数组的下标

    queue[left] = 0, queue[right] = 0; // 初始化队列，放入第一个元素

    while (++index < numsSize)
    {
        if (nums[index] == nums[queue[right]]) // 遍历到的值和右边的值相等，不处理
        {
            if (left == right) // 如果队列里只有这个值，更新它的下标
                queue[left] = index;
        }

        if (nums[index] < nums[queue[right]]) // 遍历到的值比右边的小，下标写入队列
        {
            queue[++right] = index;
        }

        while (nums[index] > nums[queue[right]]) // 遍历到的值比右边的大，则右边的值出队列
        {
// [1,3,-1,-3,5,3,6,7]
// 3
// [7,2,4]
// 2
// [1,3,1,2,0,5]
// 3
           right--;
            if (right < left) // 队列已空，写入该下标，跳出循环
            {
                right = left;
                queue[right]= index;
                break;
            }
        }

        /* 检测是否需要取值 */
        if (index >= k-1)
        {
            // 写入返回数组
            ret[ret_index++] = nums[queue[left]];

            // 检测是否需要出队列
            if (queue[left] <= index - k+1)
            {
                left++;
            }
        }
        printf("index = %d, left = %d, right = %d, ", index, left, right);
        printf("queue[left] = %d, queue[right] = %d\n", queue[left], queue[right]);
    }
    return ret;
}
// @lc code=end
