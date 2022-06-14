/*
 * @lc app=leetcode.cn id=1 lang=c
 *
 * [1] 两数之和
 *
 * https://leetcode-cn.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (52.36%)
 * Likes:    13615
 * Dislikes: 0
 * Total Accepted:    3M
 * Total Submissions: 5.8M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 *
 * 你可以按任意顺序返回答案。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [2,7,11,15], target = 9
 * 输出：[0,1]
 * 解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums = [3,2,4], target = 6
 * 输出：[1,2]
 *
 *
 * 示例 3：
 *
 *
 * 输入：nums = [3,3], target = 6
 * 输出：[0,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 2
 * -10^9
 * -10^9
 * 只会存在一个有效答案
 *
 *
 * 进阶：你可以想出一个时间复杂度小于 O(n^2) 的算法吗？
 *
 */

// @lc code=start

/* 哈希表的结构体定义 */
struct hash_entry
{
    int key;   // 以数组元素的值为 key
    int value; // 以数组元素的下标为 value

    UT_hash_handle hh; // 哈希处理句柄
};

/**
 * @brief 添加一个元素到哈希表（hash_table）中
 *
 * @param hash_table 要插入的哈希表（的指针）
 * @param key 元素的 key
 * @param value 元素的 value
 * @return struct hash_entry* 指向该插入的元素的指针（创建失败返回 NULL）
 */
struct hash_entry *hash_add(struct hash_entry **hash_table, int key, int value)
{
    // printf("hash_add: key = %d, value = %d\n", key, value);
    struct hash_entry *inserted = (struct hash_entry *)malloc(sizeof(struct hash_entry));
    if (!inserted) // 如果空间分配失败，直接返回 NULL
        return NULL;

    inserted->key = key;                     // 元素赋值，设置 key
    inserted->value = value;                 // 元素赋值，设置 value
    HASH_ADD_INT(*hash_table, key, inserted); // 将元素插入哈希表
    // printf("hash_add: inserted = %p\n", inserted);
    return inserted; // 返回插入的元素的指针
}

/**
 * @brief 根据 key 查找哈希表中的元素
 *
 * @param hash_table 要查找的哈希表（的指针）
 * @param key 要查找的元素的 key
 * @return struct hash_entry* 指向该元素的指针（查找失败将返回 NULL）
 */
struct hash_entry *hash_find(struct hash_entry **hash_table, int key)
{
    // printf("hash_find: key = %d\n", key);
    struct hash_entry *result;               // 用于存放查找结果的指针
    HASH_FIND_INT(*hash_table, &key, result); // 调用宏查找key对于的元素，并使 result 指向该元素，找不到将返回 NULL
    // if (result)
    //     printf("hash_find true: result = %p\n", result);
    // else
    //     printf("hash_find false: result = NULL\n");
    return result;
}

/**
 * @brief 删除哈希表中的元素（要先得到该元素的指针）
 *
 * @param hash_table 要删除的元素所在的哈希表（的指针）
 * @param deleted 要删除的元素的指针
 */
void hash_delete(struct hash_entry **hash_table, struct hash_entry *deleted)
{
    HASH_DEL(*hash_table, deleted);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *result = (int *)malloc(sizeof(int) * 2); // 返回的两个数
    *returnSize = 2;

    /* 指向哈希表的指针，初始化为空 */
    struct hash_entry *hash_table = NULL;

    /* 先让数组的第一个元素加入哈希表 */
    hash_add(&hash_table, nums[0], 0);

    int target_value; // 想要找的元素值（实际上是某个哈希表元素的 key）

    /* 然后从第二个元素开始找，哈希表里有没有和这个元素之和为 target 的，
        - 有就返回这两个数的下标
        - 没有就把这个数也加入哈希表（key 为值，value 为在数组中的下标）
    */
    for (int i = 1; i < numsSize; i++)
    {
        // printf("i=%d\n", i);
        target_value = target - nums[i];
        if (hash_find(&hash_table, target_value))
        {
            result[0] = i;
            result[1] = hash_find(&hash_table, target_value)->value;
            break; // 找到了，退出循环
        }
        else
        {
            hash_add(&hash_table, nums[i], i);
        }
    }

    return result;
}
// @lc code=end
