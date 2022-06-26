/*
 * @lc app=leetcode.cn id=225 lang=c
 *
 * [225] 用队列实现栈
 *
 * https://leetcode.cn/problems/implement-stack-using-queues/description/
 *
 * algorithms
 * Easy (67.56%)
 * Likes:    537
 * Dislikes: 0
 * Total Accepted:    202.9K
 * Total Submissions: 300.1K
 * Testcase Example:  '["MyStack","push","push","top","pop","empty"]\n[[],[1],[2],[],[],[]]'
 *
 * 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
 *
 * 实现 MyStack 类：
 *
 *
 * void push(int x) 将元素 x 压入栈顶。
 * int pop() 移除并返回栈顶元素。
 * int top() 返回栈顶元素。
 * boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
 *
 *
 *
 *
 * 注意：
 *
 *
 * 你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty
 * 这些操作。
 * 你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
 *
 *
 *
 *
 * 示例：
 *
 *
 * 输入：
 * ["MyStack", "push", "push", "top", "pop", "empty"]
 * [[], [1], [2], [], [], []]
 * 输出：
 * [null, null, null, 2, 2, false]
 *
 * 解释：
 * MyStack myStack = new MyStack();
 * myStack.push(1);
 * myStack.push(2);
 * myStack.top(); // 返回 2
 * myStack.pop(); // 返回 2
 * myStack.empty(); // 返回 False
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= x <= 9
 * 最多调用100 次 push、pop、top 和 empty
 * 每次调用 pop 和 top 都保证栈不为空
 *
 *
 *
 *
 * 进阶：你能否仅用一个队列来实现栈。
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// @lc code=start

/**
 * @brief 数组循环队列
 *
 */
typedef struct
{
    int *data;
    int size;
    int capacity;
    int head_index; // 队首元素的位置
} Queue;

/**
 * @brief 创建队列（动态分配） FIFO
 *
 * @param capacity 队列容量
 * @return Queue* 指向生成的队列
 */
Queue *queue_create(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->data = (int *)malloc(sizeof(int) * capacity);
    if (queue->data == NULL)
    {
        free(queue);
        return NULL;
    }
    queue->size = 0;
    queue->capacity = capacity;
    queue->head_index = 0;
    return queue;
}

/**
 * @brief 队空判断
 *
 * @param queue 目标队列
 * @retval true 队列为空
 * @retval false 队列非空
 */
bool queue_empty(Queue *queue)
{
    return queue->size == 0;
}

/**
 * @brief 队满判断
 *
 * @param queue 目标队列
 * @retval true 队列已满
 * @retval false 队列未满
 */
bool queue_full(Queue *queue)
{
    return queue->size == queue->capacity;
}

/**
 * @brief 入队
 *
 * @param queue 目标队列
 * @param value 入队元素值
 * @return int 入队元素值（新队尾）
 * @retval -1 入队失败
 */
int queue_push(Queue *queue, int value)
{
    /* 如果队列已满，则返回 -1 */
    if (queue_full(queue))
    {
        return -1;
    }

    /* 入队 */
    queue->data[(queue->head_index + queue->size) % queue->capacity] = value;
    queue->size++;
    return value;
}

/**
 * @brief 出队
 *
 * @param queue 目标队列
 * @return int 出队元素值(旧队首)
 */
int queue_pop(Queue *queue)
{
    /* 如果队列为空，则返回 -1 */
    if (queue_empty(queue))
    {
        return -1;
    }

    /* 出队 */
    int value = queue->data[queue->head_index];
    queue->head_index = (queue->head_index + 1) % queue->capacity;
    queue->size--;
    return value;
}

/**
 * @brief 栈，由两个队列实现
 *
 */
typedef struct
{
    Queue *queue_main;
    Queue *queue_bak; // 仅作为出栈时的缓冲区
    int capacity;
} MyStack;

/**
 * @brief 创建栈（动态分配）
 *
 * @return MyStack* 指向生成的栈
 */
MyStack *myStackCreate()
{
    const int capacity = 10; // 💡因为 leetcode 的函数参数没写 capacity，所以写 hardcode 在这里

    MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
    if (stack == NULL)
    {
        return NULL;
    }
    stack->queue_main = queue_create(capacity);
    if (stack->queue_main == NULL)
    {
        free(stack);
        return NULL;
    }
    stack->queue_bak = queue_create(capacity);
    if (stack->queue_bak == NULL)
    {
        free(stack->queue_main);
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    return stack;
}

/**
 * @brief 栈空判断
 *
 * @param stack 指向目标栈
 * @retval true 栈为空
 * @retval false 栈非空
 */
bool myStackEmpty(MyStack *stack)
{
    /* 如果主队列为空，则栈为空 */
    return queue_empty(stack->queue_main);
}

/**
 * @brief 栈满判断
 *
 * @param stack 指向目标栈
 * @retval true 栈已满
 * @retval false 栈未满
 */
bool myStackFull(MyStack *stack)
{
    /* 如果主队列已满，则栈已满 */
    return queue_full(stack->queue_main);
}

/**
 * @brief 入栈
 *
 * @param stack 指向目标栈
 * @param value 入栈元素值
 */
void myStackPush(MyStack *stack, int value)
{
    /* 如果栈满，直接返回 */
    if (myStackFull(stack))
    {
        return;
    }
    /* 否则写入主队列即可 */
    queue_push(stack->queue_main, value);
    // printf("push %d\n", value);
}

/**
 * @brief 出栈
 *
 * @param stack 指向目标栈
 * @return int 出栈元素值（原栈顶）
 * @retval -1 出栈失败（栈空）
 */
int myStackPop(MyStack *stack)
{
    int value = -1;
    /* 如果栈空，直接返回 -1 */
    if (myStackEmpty(stack))
    {
        return -1;
    }
    /* 出栈，具体做法是：
    1. 主队列全部出队，写入备份队列
        （其中最后一个元素是栈顶，不如备份队列，记录它的值，作为返回值）
    2. 将其余元素再从备份队列出队，写入主队列
    */

    /* 1. 主队列全部出队，写入备份队列 */
    while (!queue_empty(stack->queue_main))
    {
        /* 如果是最后一个元素，则记录它的值，作为返回值，不入备份队列 */
        if (stack->queue_main->size == 1)
        {
            value = queue_pop(stack->queue_main);
            // printf("returned value: %d\n", value);
        }
        /* 其他的元素则出主队列，入备份队列 */
        else
        {
            queue_push(stack->queue_bak, queue_pop(stack->queue_main));
        }
    }

    /* 2. 将备份队列的元素出队列，全部入主队列 */
    while (!queue_empty(stack->queue_bak))
    {
        queue_push(stack->queue_main, queue_pop(stack->queue_bak));
    }

    return value;
}

/**
 * @brief 返回栈顶元素值
 *
 * @param stack 指向目标栈
 * @return int 栈顶元素值
 * @retval -1 栈空
 */
int myStackTop(MyStack *stack)
{
    int value = -1;
    /* 如果栈空，直接返回 -1 */
    if (myStackEmpty(stack))
    {
        return -1;
    }
    /* 如果栈非空，则返回栈顶元素值 */
    /* 因为采用的是循环队列，有 head_index，结合 size 即可求得队尾元素的索引，
        不过前面已经实现了 pop，所以这里还是选择复用 pop 函数，先 pop，再 push */
    value = myStackPop(stack);
    myStackPush(stack, value);
    return value;
}

/**
 * @brief 释放栈
 *
 * @param stack 指向目标栈
 */
void myStackFree(MyStack *stack)
{
    /* 应该和 232 类似，不释放内存，只是队列大小置零 */
    stack->queue_main->size = 0;
    stack->queue_main->head_index = 0;
    stack->queue_bak->size = 0;
    stack->queue_bak->head_index = 0;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/
// @lc code=end

int main(void)
{

    /* 先测试队列功能是否正常 */
    Queue *queue = queue_create(10);
    queue_push(queue, 1);
    queue_push(queue, 2);
    queue_push(queue, 3);
    printf("queue_pop: %d\n", queue_pop(queue));
    printf("queue_empty: %d\n", queue_empty(queue));
    printf("queue_full: %d\n", queue_full(queue));

    /* 再测试栈功能是否正常 */
    MyStack *stack = myStackCreate();
    myStackPush(stack, 1);
    int param_2 = myStackPop(stack);
    int param_3 = myStackTop(stack);
    bool param_4 = myStackEmpty(stack);

    printf("param_2: %d\n", param_2);
    printf("param_3: %d\n", param_3);
    printf("param_4: %d\n", param_4);

    return 0;
}
