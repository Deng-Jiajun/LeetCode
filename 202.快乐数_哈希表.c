/*
 * @lc app=leetcode.cn id=202 lang=c
 *
 * [202] 快乐数
 *
 * https://leetcode.cn/problems/happy-number/description/
 *
 * algorithms
 * Easy (62.87%)
 * Likes:    954
 * Dislikes: 0
 * Total Accepted:    257.3K
 * Total Submissions: 409K
 * Testcase Example:  '19'
 *
 * 编写一个算法来判断一个数 n 是不是快乐数。
 *
 * 「快乐数」 定义为：
 *
 *
 * 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 * 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 * 如果这个过程 结果为 1，那么这个数就是快乐数。
 *
 *
 * 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 19
 * 输出：true
 * 解释：
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 2
 * 输出：false
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 2^31 - 1
 *
 *
 */

// @lc code=start
/* 哈希表的结构体定义 */
struct hash_entry
{
    int key; // 以数值为 key
    // 这题不用 value

    UT_hash_handle hh; // 哈希处理句柄
};

/**
 * @brief 添加一个元素到哈希表（hash_table）中
 *
 * @param hash_table 要插入的哈希表（的指针）
 * @param key 元素的 key
 * @return struct hash_entry* 指向该插入的元素的指针（创建失败返回 NULL）
 */
struct hash_entry *hash_add(struct hash_entry **hash_table, int key)
{
    struct hash_entry *inserted = (struct hash_entry *)malloc(sizeof(struct hash_entry));
    if (!inserted) // 如果空间分配失败，直接返回 NULL
        return NULL;

    inserted->key = key; // 元素赋值，设置 key

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

/* 鬼知道该取什么名字，总之就是逐位的平方求和 */
int calc(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}

bool isHappy(int n)
{
    /* 总之就是把 calc 的计算结果放入哈希表，如果出现了相同的数，就说明是循环的 */
    struct hash_entry *hash_table = NULL;
    struct hash_entry *hash_temp = NULL;
    int num = calc(n);
    hash_add(&hash_table, num);
    while (1)
    {
        num = calc(num);
        if (num == 1)
            return true;

        hash_temp = hash_find(&hash_table, num);
        
        if (hash_temp)
            return false;

        hash_add(&hash_table, num);
    }
}
// @lc code=end
