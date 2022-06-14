/*
 * @lc app=leetcode.cn id=454 lang=c
 *
 * [454] 四数相加 II
 *
 * https://leetcode.cn/problems/4sum-ii/description/
 *
 * algorithms
 * Medium (62.86%)
 * Likes:    587
 * Dislikes: 0
 * Total Accepted:    126.1K
 * Total Submissions: 200.5K
 * Testcase Example:  '[1,2]\n[-2,-1]\n[-1,2]\n[0,2]'
 *
 * 给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l)
 * 能满足：
 *
 *
 * 0 <= i, j, k, l < n
 * nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
 * 输出：2
 * 解释：
 * 两个元组如下：
 * 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) +
 * (-1) + 2 = 0
 * 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) +
 * (-1) + 0 = 0
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == nums1.length
 * n == nums2.length
 * n == nums3.length
 * n == nums4.length
 * 1 <= n <= 200
 * -2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28
 *
 *
 */

// @lc code=start

/* 哈希表的结构体定义 */
struct hash_entry
{
    int key;   // 以两个数的和为 key
    int value; // 以两个数的和出现的次数为 value

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

int fourSumCount(int *nums1, int nums1Size, int *nums2, int nums2Size, int *nums3, int nums3Size, int *nums4, int nums4Size)
{
    /* 分两组，分别求和，写入哈希表，并统计次数 */

    /* 两个哈希表，分别记录 nums1 和 nums2、nums3 和 nums4 之和及出现次数 */
    struct hash_entry *hash_table = NULL; // nums1[i] + nums2[j]

    int count = 0; // 和为 0 的次数
    int temp;
    struct hash_entry *hash_temp;

    /* 计算 hash_table */
    for (int i = 0; i != nums1Size; i++)
    {
        for (int j = 0; j != nums2Size; j++)
        {
            /* 把 nums1[i] + nums2[j] 的和放入哈希表1 */
            temp = nums1[i] + nums2[j];
            hash_temp = hash_find(&hash_table, temp);
            if (hash_temp)
                hash_temp->value++;
            else
                hash_add(&hash_table, temp, 1);
        }
    }

    /* 求解和为 0 的次数 */
    for (int i = 0; i != nums3Size; i++)
    {
        for (int j = 0; j != nums4Size; j++)
        {
            temp = 0 - (nums3[i] + nums4[j]);
            hash_temp = hash_find(&hash_table, temp);
            if (hash_temp)
                count += hash_temp->value;
        }
    }

    return count;
}
// @lc code=end
