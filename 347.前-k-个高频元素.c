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
#include "uthash.h"
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

/* 用链表的形式定义一个优先级队列 */
typedef struct PriorityQueueNode{
    int num;   // 数字
    int count; // 出现的次数
    struct PriorityQueueNode* next;
}PriorityQueue,PriorityQueueNode;

int PRIORITY_QUEUE_CAPACITY = 0; // 优先级队列的容量
int priorityQueueSize = 0;     // 优先级队列的大小

/**
 * @brief 创建一个优先级队列
 * 
 * @return PriorityQueue* 
 */
PriorityQueue* PriorityQueueCreate(void)
{
    PriorityQueue* head = (PriorityQueue *)malloc(sizeof(PriorityQueue)); // 虚拟头结点
    head->next = NULL;
    priorityQueueSize = 0;
    return head;
}

/**
 * @brief 向优先级队列中插入一个元素
 * 
 * @param priority_queue 优先级队列
 * @param num 要插入的元素
 * @param count 要插入的元素的出现次数
 * 
 * @note 要求：
 * @note 1. 优先级队列中的元素按照出现次数从小到大排列
 * @note 2. 优先级队列的容量为 PRIORITY_QUEUE_CAPACITY
 * @note 3. 如果优先级队列已满，就选择合适的位置插入
 */
void PriorityQueueInsert(PriorityQueue* priority_queue, int num, int count)
{
    if (priorityQueueSize == PRIORITY_QUEUE_CAPACITY) { // 如果优先级队列已满

        /* 如果要插入的元素的出现次数小于队首元素的出现次数，直接返回 */
        if (priority_queue->next->count > count) return; 

        /* 沿着队列一个个往后找
           如果遍历到的元素的出现次数小于要插入的元素的出现次数，就把下一个元素的 num 和 count 赋值给当前元素
           直到遍历到的元素的出现次数大于等于要插入的元素的出现次数，或者遍历到了队尾，把 num 和 count 赋值给当前元素 */
        PriorityQueueNode* tmp = priority_queue;
        while (tmp->next && tmp->next->count < count) {
            tmp->num   = tmp->next->num;
            tmp->count = tmp->next->count;
            tmp        = tmp->next;
        }
        tmp->num   = num;
        tmp->count = count;
    } else { // 如果优先级队列未满，找个合适的位置插入
        PriorityQueueNode* tmp = priority_queue;
        while (tmp->next && tmp->next->count < count) {
            tmp = tmp->next;
        }
        PriorityQueueNode* newNode = (PriorityQueueNode *)malloc(sizeof(PriorityQueueNode));
        newNode->num   = num;
        newNode->count = count;
        newNode->next  = tmp->next;
        tmp->next      = newNode;
        priorityQueueSize++;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    /* 用哈希表记录出现次数 */
    struct hash_entry* hash_table = NULL; // 指向哈希表的指针，初始化为空
    for (int i = 0; i < numsSize; i++) {
        struct hash_entry* result = hash_find(&hash_table, nums[i]);
        if (result) {
            result->value++;
        } else {
            hash_add(&hash_table, nums[i], 1);
        }
    }
    // printf("hash_table size: %d\n", HASH_COUNT(hash_table));
    // printf("hash_table content:\n");
    // struct hash_entry *tmp;
    // for (tmp = hash_table; tmp != NULL; tmp = tmp->hh.next) {
    //     printf("key: %d, value: %d\n", tmp->key, tmp->value);
    // }

    PRIORITY_QUEUE_CAPACITY = k; // 设置优先级队列的容量
    PriorityQueue* priority_queue = PriorityQueueCreate(); // 创建优先级队列
    
    /* 遍历整个哈希表，逐个尝试插入优先级队列 */
    for (struct hash_entry *tmp = hash_table; tmp != NULL; tmp = tmp->hh.next) {
        PriorityQueueInsert(priority_queue, tmp->key, tmp->value);
    }

    /* 从优先级队列里取数据，就是最终的结果 */
    int* result = (int *)malloc(sizeof(int) * k);
    PriorityQueueNode* tmp = priority_queue->next;
    for (int i = 0; i < k; i++) {
        result[i] = tmp->num;
        tmp = tmp->next;
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
