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

    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize * numsSize);
    *returnSize = 0;

    /* 按照循环的顺序，得到的 result 中 i < j < k */
    for (int i = 0; i < numsSize; i++)
        for (int j = i + 1; j < numsSize; j++)
            for (int k = j + 1; k < numsSize; k++)
            {
                // /* 求 nums[k]，使得 nums[i] + nums[j] + nums[k] = 0 */
                if (nums[i] + nums[j] + nums[k] == 0)
                {
                    printf("%d %d %d\n", nums[i], nums[j], nums[k]);

                    result[*returnSize] = (int *)malloc(sizeof(int) * 3);
                    if (result[*returnSize])
                    {
                        printf("result[%d] mallco ok\n", *returnSize);

                        result[*returnSize][0] = nums[i];
                        result[*returnSize][1] = nums[j];
                        result[*returnSize][2] = nums[k];
                        (*returnSize)++;
                    }
                }
            }

    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i != *returnSize; i++)
        (*returnColumnSizes)[i] = 3;

    /* 结果中可能存在重复的三元组，需要去重 */

    /* 先排序 */
    for (int i = 0; i != *returnSize; i++)
        qsort(result[i], 3, sizeof(int), cmp);

    /* 再去重 */
    for (int i = 0; i != *returnSize; i++)
    {
        for (int j = i + 1; j != *returnSize; j++)
        {
            if (result[i][0] == result[j][0] && result[i][1] == result[j][1] && result[i][2] == result[j][2])
            {
                for (int k = j; k != *returnSize - 1; k++)
                {
                    result[k] = result[k + 1];
                }
                (*returnSize)--;
                j--;
            }
        }
    }

    return result;
}
// @lc code=end
