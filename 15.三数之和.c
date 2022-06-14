/*
 * @lc app=leetcode.cn id=15 lang=c
 *
 * [15] 三数之和
 *
 * https://leetcode.cn/problems/3sum/description/
 *
 * algorithms
 * Medium (35.57%)
 * Likes:    4865
 * Dislikes: 0
 * Total Accepted:    1M
 * Total Submissions: 2.8M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0
 * 且不重复的三元组。
 *
 * 注意：答案中不可以包含重复的三元组。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [-1,0,1,2,-1,-4]
 * 输出：[[-1,-1,2],[-1,0,1]]
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = []
 * 输出：[]
 *
 *
 * 示例 3：
 *
 *
 * 输入：nums = [0]
 * 输出：[]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 0
 * -10^5
 *
 *
 */

// @lc code=start

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    if (numsSize < 3)
    {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    /* 排序 */
    qsort(nums, numsSize, sizeof(int), cmp);

    /* 双指针找结果集 */
    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);
    *returnSize = 0;

    int left;
    int right;
    int sum;

    /* 在[i + 1, numsSize - 1]找 nums[i] 对应的另外两个数 */
    for (int i = 0; i < numsSize - 2; i++)
    {
        /* 由于数组的有序性，如果 nums[i] 已经大于 0，则后面的数字必然大于 0，不需要再找 */
        if (nums[i] > 0)
            break;

        left = i + 1;
        right = numsSize - 1;
        while (left < right)
        {
            sum = nums[i] + nums[left] + nums[right];
            if (sum < 0)
                left++;
            else if (sum > 0)
                right--;
            else // ==0
            {
                result[*returnSize] = (int *)malloc(sizeof(int) * 3);
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnSize)++;
                // break;
                /* 👆不能 break，还有其他的可能，但是需要缩范围 */
                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;

                /* 缩范围 */
                left++;
                right--;
            }
        }

        /* i 前推，避免重复 */
        while (i < numsSize - 3 && nums[i] == nums[i + 1])
            i++;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 3;

    return result;
}
// @lc code=end
