/*
 * @lc app=leetcode.cn id=232 lang=c
 *
 * [232] 用栈实现队列
 *
 * https://leetcode.cn/problems/implement-queue-using-stacks/description/
 *
 * algorithms
 * Easy (68.80%)
 * Likes:    680
 * Dislikes: 0
 * Total Accepted:    248.9K
 * Total Submissions: 361.6K
 * Testcase Example:  '["MyQueue","push","push","peek","pop","empty"]\n[[],[1],[2],[],[],[]]'
 *
 * 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
 *
 * 实现 MyQueue 类：
 *
 *
 * void push(int x) 将元素 x 推到队列的末尾
 * int pop() 从队列的开头移除并返回元素
 * int peek() 返回队列开头的元素
 * boolean empty() 如果队列为空，返回 true ；否则，返回 false
 *
 *
 * 说明：
 *
 *
 * 你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty
 * 操作是合法的。
 * 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：
 * ["MyQueue", "push", "push", "peek", "pop", "empty"]
 * [[], [1], [2], [], [], []]
 * 输出：
 * [null, null, null, 1, 1, false]
 *
 * 解释：
 * MyQueue myQueue = new MyQueue();
 * myQueue.push(1); // queue is: [1]
 * myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
 * myQueue.peek(); // return 1
 * myQueue.pop(); // return 1, queue is [2]
 * myQueue.empty(); // return false
 *
 *
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= x <= 9
 * 最多调用 100 次 push、pop、peek 和 empty
 * 假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作）
 *
 *
 *
 *
 * 进阶：
 *
 *
 * 你能否实现每个操作均摊时间复杂度为 O(1) 的队列？换句话说，执行 n 个操作的总时间复杂度为 O(n) ，即使其中一个操作可能花费较长时间。
 *
 *
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
// @lc code=start

/**
 * @brief 栈，动态分配内存空间
 *
 */
typedef struct
{
    int *data;
    int size;
    int capacity;
} Stack;

/**
 * @brief 创建栈
 *
 * @param capacity 栈容量
 * @return Stack* 指向创建的栈
 * @retval NULL 创建失败
 */
Stack *stack_create(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return NULL;
    }
    stack->data = (int *)malloc(sizeof(int) * capacity);
    if (stack->data == NULL)
    {
        free(stack);
        return NULL;
    }
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

/**
 * @brief 出栈
 *
 * @param stack 指向目标栈
 * @return int 指向出栈元素的值
 * @retval -1 出栈失败(栈空)
 */
int stack_pop(Stack *stack)
{
    return stack->size ? stack->data[--stack->size] : -1;
}

/**
 * @brief 返回栈顶元素的值
 *
 * @param stack 指向目标栈
 * @return int 指向栈顶元素的值
 * @retval -1 栈空
 */
int stack_top(Stack *stack)
{
    return stack->size ? stack->data[stack->size - 1] : -1;
}

/**
 * @brief 入栈
 *
 * @param stack 指向目标栈
 * @param value 入栈的元素的值
 * @return int 新栈顶元素的值
 * @retval -1 入栈失败(栈满)
 */
int stack_push(Stack *stack, int value)
{
    if (stack->size == stack->capacity)
        return -1;
    stack->data[(stack->size)++] = value;
    return value;
}

/**
 * @brief 获取栈内元素个数
 *
 * @param stack 指向目标栈
 * @return int 栈内元素个数
 */
int stack_size(Stack *stack)
{
    return stack->size;
}

/**
 * @brief 栈空判断
 *
 * @param stack 指向目标栈
 * @return true 栈空
 * @return false 栈非空
 */
bool stack_empty(Stack *stack)
{
    return stack->size == 0;
}

/**
 * @brief 栈满判断
 *
 * @param stack 指向目标栈
 * @return true 栈满
 * @return false 栈非满
 */
bool stack_full(Stack *stack)
{
    return stack->size == stack->capacity;
}

/**
 * @brief 两个栈实现队列（FIFO）
 *
 */
typedef struct
{
    Stack *stack_in;
    Stack *stack_out;
} MyQueue;

/**
 * @brief 初始化队列
 *
 * @return MyQueue* 指向创建的队列
 * @retval NULL 创建失败
 */
MyQueue *myQueueCreate()
{
    MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->stack_in = stack_create(10);
    if (queue->stack_in == NULL)
    {
        free(queue);
        return NULL;
    }
    queue->stack_out = stack_create(10);
    if (queue->stack_out == NULL)
    {
        free(queue->stack_in);
        free(queue);
        return NULL;
    }
    return queue;
}

/**
 * @brief 队列空判断
 *
 * @param queue 指向目标队列
 * @retval true 队列空
 * @retval false 队列非空
 */
bool myQueueEmpty(MyQueue *queue)
{
    /* 如果输入栈、输出栈都为空，则队列为空 */
    return stack_empty(queue->stack_in) && stack_empty(queue->stack_out);
}

/**
 * @brief 入队
 *
 * @param queue 指向目标队列
 * @param value 入队的元素的值
 */
void myQueuePush(MyQueue *queue, int value)
{
    /* 压入输入栈即可 */
    if (stack_full(queue->stack_in))
    {
        printf("stack_in is full\n");
        return;
    }
    stack_push(queue->stack_in, value);
}

/**
 * @brief 出队
 *
 * @param queue 指向目标队列
 * @return int 出队元素的值
 * @retval -1 出队失败(队列空)
 */
int myQueuePop(MyQueue *queue)
{
    /* 如果队列为空，则返回 -1 */
    if  (myQueueEmpty(queue))
    {
        printf("queue is empty\n");
        return -1;
    }
    
    /* 如果输出栈为空，则将输入栈中的元素全部压入输出栈 */
    if (stack_empty(queue->stack_out))
    {
        while (!stack_empty(queue->stack_in))
        {
            stack_push(queue->stack_out, stack_pop(queue->stack_in));
        }
    }
    return stack_pop(queue->stack_out);

    /* 如果输出栈不为空，则直接出栈即可 */
    // return stack_pop(queue->stack_out);
}

/**
 * @brief 获取队首元素的值
 *
 * @param queue 指向目标队列
 * @return int 队首元素的值
 */
int myQueuePeek(MyQueue *queue)
{
    /* 调用 myQueuePop 函数，读出元素值，再写回输出栈 */
    int value = myQueuePop(queue);
    stack_push(queue->stack_out, value);
    return value;

    /* 💡因为 pop 操作在返回前都会让输出栈里有元素，然后再 pop，
        所以 peek 的时候必须要把这个 pop 出来的元素再 push 回输出栈，
        而不是调用 myQueuePush 函数将元素入队 */
}


/**
 * @brief 队列清空
 *
 * @param queue 指向目标队列
 */
void myQueueFree(MyQueue *queue)
{
    /* 把大小置零即可，空间释放由 leetcode 负责 */
    queue->stack_in->size = 0;
    queue->stack_out->size = 0;
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/
// @lc code=end

int main(void)
{
    MyQueue *queue = myQueueCreate();
    myQueuePush(queue, 1);
    myQueuePush(queue, 2);
    int param_2 = myQueuePeek(queue);
    int param_3 = myQueuePop(queue);
    int param_4 = myQueueEmpty(queue);
    printf("%d %d %d %d\n", param_2, param_3, param_4, queue->stack_in->size);
    return 0;
}
