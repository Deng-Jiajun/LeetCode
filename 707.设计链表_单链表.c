/*
 * @lc app=leetcode.cn id=707 lang=c
 *
 * [707] 设计链表
 *
 * https://leetcode.cn/problems/design-linked-list/description/
 *
 * algorithms
 * Medium (33.68%)
 * Likes:    466
 * Dislikes: 0
 * Total Accepted:    121.4K
 * Total Submissions: 360.1K
 * Testcase Example:  '["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIndex","get"]\n' +
  '[[],[1],[3],[1,2],[1],[1],[1]]'
 *
 * 设计链表的实现。您可以选择使用单链表或双链表。单链表中的节点应该具有两个属性：val 和 next。val 是当前节点的值，next
 * 是指向下一个节点的指针/引用。如果要使用双向链表，则还需要一个属性 prev 以指示链表中的上一个节点。假设链表中的所有节点都是 0-index 的。
 *
 * 在链表类中实现这些功能：
 *
 *
 * get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
 * addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
 * addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
 * addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index
 * 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
 * deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
 *
 *
 *
 *
 * 示例：
 *
 * MyLinkedList linkedList = new MyLinkedList();
 * linkedList.addAtHead(1);
 * linkedList.addAtTail(3);
 * linkedList.addAtIndex(1,2);   //链表变为1-> 2-> 3
 * linkedList.get(1);            //返回2
 * linkedList.deleteAtIndex(1);  //现在链表是1-> 3
 * linkedList.get(1);            //返回3
 *
 *
 *
 *
 * 提示：
 *
 *
 * 所有val值都在 [1, 1000] 之内。
 * 操作次数将在  [1, 1000] 之内。
 * 请不要使用内置的 LinkedList 库。
 *
 *
 */

// @lc code=start

/**
 * @brief 单链表定义
 *
 */
typedef struct MyLinkedList_t
{
    int val;
    struct MyLinkedList_t *next;
} MyLinkedList;

/**
 * @brief 构建一个带头节点的单链表
 *
 * @return MyLinkedList* 单链表的头节点
 */
MyLinkedList *myLinkedListCreate()
{
    MyLinkedList *head = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    head->next = NULL;
    return head;
}

/**
 * @brief 获取索引为index的节点的值
 *
 * @param obj MyLinkedList* 单链表的头节点
 * @param index 节点的索引
 * @return int 节点的值
 */
int myLinkedListGet(MyLinkedList *obj, int index)
{
    /* 如果 index 小于 0，或链表为空，返回 -1 */
    if (index < 0 || obj->next == NULL)
        return -1;

    /* 按照 index 进行遍历 */
    int i = 0; // 要访问的节点索引
    while (obj->next)
    {
        if (i == index)
            return obj->next->val;

        obj = obj->next; // 赋值之后，node 指向索引为 i 的节点
        i++;             // i 自增后，表示下一次迭代时，要访问的节点索引
    }

    /* 如果走出了循环，说明 index 无效，返回 -1 */
    return -1;
}

/**
 * @brief 创建值为 val 的节点，插入到 left 和 right 之间
 *
 * @param left 左节点
 * @param right 右节点
 * @param val 节点的值
 *
 * @note 不需要担心 left 和 right 是否有接续关系，在这个函数看来，
 *  left 和 right 是孤立的两个节点，修改 left->next 不会影响 right，
 *  它要做的就是把新节点插到 left 和 right 之间而已
 */
void myLinkedListInsert(MyLinkedList *left, MyLinkedList *right, int val)
{
    MyLinkedList *newNode = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    newNode->val = val;    // 节点赋值
    left->next = newNode;  // 连接左侧
    newNode->next = right; // 连接右侧
}

/**
 * @brief 在链表的第一个元素之前添加一个值为 val 的节点
 *
 * @param obj MyLinkedList* 单链表的头节点
 * @param val 节点的值
 */
void myLinkedListAddAtHead(MyLinkedList *obj, int val)
{
    /* 然后创建新节点并把它插入到头节点之后 */
    myLinkedListInsert(obj, obj->next, val);
}

/**
 * @brief 在链表的最后一个元素之后添加一个值为 val 的节点
 *
 * @param obj MyLinkedList* 单链表的头节点
 * @param val 节点的值
 */
void myLinkedListAddAtTail(MyLinkedList *obj, int val)
{
    /* 遍历到最后一个节点 */
    MyLinkedList *node = obj;
    while (node->next)
        node = node->next;

    /* 然后创建新节点并插入 */
    myLinkedListInsert(node, NULL, val);
}

/**
 * @brief 在链表的第 index 个节点之前添加一个值为 val 的节点
 *
 * @param obj MyLinkedList* 单链表的头节点
 * @param index 节点的索引
 * @param val 节点的值
 */
void myLinkedListAddAtIndex(MyLinkedList *obj, int index, int val)
{
    /* 如果 index <= 0，就在头节点之后插入 */
    if (index <= 0)
    {
        myLinkedListAddAtHead(obj, val);
    }
    else /* 其他情况下就遍历到第 index-1 个节点，然后插入到它后面 */
    {
        MyLinkedList *node = obj;
        int i = 0;
        while (node->next)
        {
            if (i == index) /* 💡注意，这个时候 node 指向索引为 index-1 的节点 */
            {
                /* 插入到 第 index-1 个节点之后 */
                myLinkedListInsert(node, node->next, val);
                return; // 插入完成，退出函数
            }
            node = node->next; // 赋值之后，node 指向索引为 i 的节点
            i++;               // i 自增后，表示下一次迭代时，要访问的节点索引
        }
        /* 如果 i==index，就把新节点插到链表末尾 */
        if (i == index)
            myLinkedListInsert(node, NULL, val); // node 指向索引为 index-1 的节点
        /* 这个条件判断可以加到 while 循环里，但是单独拎出来逻辑上更清晰 */
    }
}

/**
 * @brief 删除链表上索引为 index 的节点
 *
 * @param obj MyLinkedList* 单链表的头节点
 * @param index 节点的索引
 */
void myLinkedListDeleteAtIndex(MyLinkedList *obj, int index)
{
    /* 如果 index < 0，或链表为空，就不做任何事情 */
    if (index < 0 || obj->next == NULL)
    {
        return;
    }
    else /* 其他情况下就遍历到第 index-1 个节点，然后删除后面的那个节点 */
    {
        MyLinkedList *node = obj;
        int i = 0;
        while (node->next)
        {
            if (i == index) /* 💡注意，这个时候 node 指向索引为 index-1 的节点 */
            {
                /* 删除后面的那个节点（索引为 index） */
                MyLinkedList *deleted = node->next;
                node->next = deleted->next;
                free(deleted);
                return; // 删除完成，退出函数
            }
            node = node->next; // 赋值之后，node 指向索引为 i 的节点
            i++;               // i 自增后，表示下一次迭代时，要访问的节点索引
        }
        /* 如果走出了循环，说明 index 无效，正常退出函数 */
    }
}

/**
 * @brief 释放链表
 *
 * @param obj MyLinkedList* 单链表的头节点
 */
void myLinkedListFree(MyLinkedList *obj)
{
    MyLinkedList *node = obj;
    while (node->next)
    {
        MyLinkedList *deleted = node->next;
        node->next = deleted->next;
        free(deleted);
    }
    free(obj);
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
*/
// @lc code=end
