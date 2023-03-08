/*
 * @lc app=leetcode.cn id=347 lang=c
 *
 * [347] 前 K 个高频元素
 *
 * https://leetcode.cn/problems/top-k-frequent-elements/description/
 *
 * algorithms
 * Medium (63.49%)
 * Likes:    1469
 * Dislikes: 0
 * Total Accepted:    396.5K
 * Total Submissions: 624.4K
 * Testcase Example:  '[1,1,1,2,2,3]\n2'
 *
 * 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [1,1,1,2,2,3], k = 2
 * 输出: [1,2]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [1], k = 1
 * 输出: [1]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * k 的取值范围是 [1, 数组中不相同的元素的个数]
 * 题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
 * 
 * 
 * 
 * 
 * 进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// @lc code=start


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    int numArray[numsSize];
    int countArray[numsSize];
    memset(countArray, 0, sizeof(countArray));

    /* 遍历 nums，逐一填入 numArray，如果已存在，则让countArray 对应的位置+1 */
    int numArraySize = 0; // 不同元素的个数
    for (int i = 0; i < numsSize; i++)
    {
        int j = 0;
        for (; j < numArraySize; j++)
        {
            if (nums[i] == numArray[j])
            {
                countArray[j]++;
                break;
            }
        }
        if (j == numArraySize)
        {
            numArray[numArraySize] = nums[i];
            countArray[numArraySize]++;
            numArraySize++;
        }
    }

    /* 选择排序，将 countArray 从大到小排序，同时将 numArray 与之对应 */
    for (int i = 0; i < numArraySize - 1; i++)
    {
        for (int j = i + 1; j < numArraySize; j++)
        {
            if (countArray[i] < countArray[j])
            {
                int temp = countArray[i];
                countArray[i] = countArray[j];
                countArray[j] = temp;
                
                temp = numArray[i];
                numArray[i] = numArray[j];
                numArray[j] = temp;
            }
        }
    }

    /* 将 numArray 前 k 个元素返回 */
    int *result = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
    {
        result[i] = numArray[i];
    }

    *returnSize = k;
    return result;
}
// @lc code=end

int main(void)
{
    int nums[] = {1,1,1,2,2,3};
    int k = 2;
    int returnSize = 0;
    int *result = topKFrequent(nums, sizeof(nums)/sizeof(int), k, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", result[i]);
    }
    return 0;
}
