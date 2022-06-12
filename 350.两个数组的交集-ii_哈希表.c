/*
 * @lc app=leetcode.cn id=350 lang=c
 *
 * [350] 两个数组的交集 II
 *
 * https://leetcode.cn/problems/intersection-of-two-arrays-ii/description/
 *
 * algorithms
 * Easy (56.23%)
 * Likes:    768
 * Dislikes: 0
 * Total Accepted:    362.7K
 * Total Submissions: 644.8K
 * Testcase Example:  '[1,2,2,1]\n[2,2]'
 *
 * 给你两个整数数组 nums1 和 nums2
 * ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,2,2,1], nums2 = [2,2]
 * 输出：[2,2]
 *
 *
 * 示例 2:
 *
 *
 * 输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * 输出：[4,9]
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums1.length, nums2.length <= 1000
 * 0 <= nums1[i], nums2[i] <= 1000
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 如果给定的数组已经排好序呢？你将如何优化你的算法？
 * 如果 nums1 的大小比 nums2 小，哪种方法更优？
 * 如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？
 *
 *
 */

// @lc code=start

/* 哈希表的结构体定义 */
struct hash_entry
{
    int key;   // 以数值为 key
    int value; // 以数值出现次数为 value

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
    struct hash_entry *inserted = (struct hash_entry *)malloc(sizeof(struct hash_entry));
    if (!inserted) // 如果空间分配失败，直接返回 NULL
        return NULL;

    inserted->key = key;                      // 元素赋值，设置 key
    inserted->value = value;                  // 元素赋值，设置 value
    HASH_ADD_INT(*hash_table, key, inserted); // 将元素插入哈希表
    return inserted;                          // 返回插入的元素的指针
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
    struct hash_entry *result;                // 用于存放查找结果的指针
    HASH_FIND_INT(*hash_table, &key, result); // 调用宏查找key对于的元素，并使 result 指向该元素，找不到将返回 NULL
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
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{

    int *result = (int *)malloc(sizeof(int) * nums1Size);
    *returnSize = 0;
    struct hash_entry *hash_table = NULL; // 指向哈希表的指针
    struct hash_entry *hash_temp = NULL;  // 指向某个哈希表中元素的指针

    /* 遍历第一个数组，记录每个数字出现的次数，并存入哈希表 */
    for (int i = 0; i < nums1Size; i++)
    {
        /* 先找该数字在哈希表中是否存在：
        - 如果有，就让它的 value 自增 1
        - 如果没有，就把它加入哈希表，并记 value 为 1 */
        hash_temp = hash_find(&hash_table, nums1[i]);
        if (hash_temp)
            hash_temp->value++;
        else
            hash_add(&hash_table, nums1[i], 1);
    }

    /* 遍历第二个数组，查找哈希表中是否存在该数字
        如果存在，将其输出到结果数组中，并使其 value 自减 1
        （若 --value == 0，则从哈希表中删除该元素） */
    for (int i = 0; i < nums2Size; i++)
    {
        hash_temp = hash_find(&hash_table, nums2[i]);
        if (hash_temp)
        {
            result[*returnSize] = nums2[i];
            (*returnSize)++;
            hash_temp->value--;
            if (hash_temp->value == 0)
                hash_delete(&hash_table, hash_temp);
        }
    }

    return result;
}
// @lc code=end
