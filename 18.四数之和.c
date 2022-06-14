/*
 * @lc app=leetcode.cn id=18 lang=c
 *
 * [18] 四数之和
 *
 * https://leetcode.cn/problems/4sum/description/
 *
 * algorithms
 * Medium (39.31%)
 * Likes:    1274
 * Dislikes: 0
 * Total Accepted:    328.6K
 * Total Submissions: 835.6K
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a],
 * nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
 *
 *
 * 0 <= a, b, c, d < n
 * a、b、c 和 d 互不相同
 * nums[a] + nums[b] + nums[c] + nums[d] == target
 *
 *
 * 你可以按 任意顺序 返回答案 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,0,-1,0,-2,2], target = 0
 * 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [2,2,2,2,2], target = 8
 * 输出：[[2,2,2,2]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 200
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 *
 *
 */

// @lc code=start

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes)
{
    if (numsSize < 4)
    {
        *returnSize = 0;
        return NULL;
    }

    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);
    *returnSize = 0;

    /* 先排序 */
    qsort(nums, numsSize, sizeof(int), comp);

    /* 两层for循环确定两个数 */
    for (int i = 0; i < numsSize - 3; i++)
    {
        for (int j = i + 1; j < numsSize - 2; j++)
        {
            int sum_find = target - (nums[i] + nums[j]);
            /* 双指针找剩下的两个数，其和为 sum_find */
            int left = j + 1, right = numsSize - 1;
            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum == sum_find)
                {
                    result[*returnSize] = (int *)malloc(sizeof(int) * 4);
                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[j];
                    result[*returnSize][2] = nums[left];
                    result[*returnSize][3] = nums[right];
                    (*returnSize)++;

                    /* 缩范围 */
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    /* 定范围 */
                    left++, right--;
                }
                else if (sum < sum_find)
                    left++;
                else // sum > sum_find
                    right--;
            }

            /* 前推，避免重复 */
            while (j < numsSize - 2 && nums[j] == nums[j + 1])
                j++;
        }

        /* 前推，避免重复 */
        while (i < numsSize - 3 && nums[i] == nums[i + 1])
            i++;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 4;

    return result;
}
// @lc code=end
