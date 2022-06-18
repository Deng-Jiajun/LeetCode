> 顺序： https://programmercarl.com/
# 数组

## [704. 二分查找](https://leetcode-cn.com/problems/binary-search/)

[题解](https://programmercarl.com/0704.二分查找.html#_704-二分查找)

二分法思路简单，但是要注意，二分法要求数组元素**有序且唯一**。有序是二分法的前提，如果元素不唯一，也能找得到，但是返回的下标也**可能不唯一**

然后是区间的开闭问题，也就是搜索范围是否包括边界，区间的选取问题会导致 `left` 和 `right` 的比较是否要 `=`，`middle` 的改变是否要 `+/- 1`，还是直接 `=`。区间选取没有优劣，但是要保证其统一，本质上还是边界处理问题，这里我选择全闭 `[ ]`

### 相关题目

#### [35. 搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)

[题解](https://programmercarl.com/0035.搜索插入位置.html)

这题和 704 一样，二分查找，区别在于没找到的时候要返回**按序插入的位置**

所以如果没找到，这个位置这么确定呢？

大致分为三种情况

1. 头部插入（0）

   这种情况位置 = middle（也就是 **left**，因为这个值太小，left没变过，一直是0）

2. 中间插入（numSize)

   这种情况，如果 target < nums[middle]，那位置就是 middle（也就是 **left**，因为要往左边找）

   ​					如果 target > nums[middle]，那位置就是 middle+1（也就是 **left**，因为要往右边找）

3. 尾部插入（middle?）

   这种情况位置 = middle+1（也就是**left**，因为太大，所以要往右)

因此，最终结论是：**全都返回 left 就行了**

这个结果的奇妙之处在于，最后一次循环，**middle=left=right**，因为左边找不到比 middle 小的数了，所以如果目标值比当前的值小，则目标值就要插到当前的位置，即 left，而 right 根据逻辑会等于 middle-1，不影响 left 的值；而如果目标值比当前的值大，则目标值要插到当前位置的后面，即 middle+1，而 left 根据逻辑会等于 middle+1，而这个 left 的新值正好就是我们需要的。（💡注意，同样的，也可以返回 **right+1**）

❗把握住一点：如果没有找到目标元素，则右指针会指向最大小于 target 的值，左指针指向最小大于 target 的值。（注意，这指的是 left 和 right 还没有改变的时候）**这个规律很明确，但是太拗口，实际上，如果逻辑清晰的情况下，这个规律并不好用，因为这句话本身太过复杂**

其实还有一个简单的办法：直接在 left==right 但是当前值又不是目标值的时候，直接判断 target 和当前值的大小，target 大于当前值，就直接返回 middle+1，反之返回 middle-1，当然这样会增加时间复杂度，不过本着写的就是垃圾代码的厚脸皮心态，这种做法也不是不行（没有暴力破解就不错了）



#### [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

[题解](https://programmercarl.com/0034.在排序数组中查找元素的第一个和最后一个位置.html)

首先 O(log n) 的时间复杂度指明了需要使用二分查找

最朴素的想法，在二分法的基础上，找到 `targetIndex` 后，**一格格地左右探**，就能探明起始位置。但是这一块的时间复杂度是这里的复杂度是 O(m)（m是目标值的数量） ，显然不满足 O(log n) （总时间复杂度是O(log n + m) ）。时间复杂度不符合要求的原因也很简单，在查找到目标元素后，**二分查找退化为了线性查找**，因而时间复杂度不符合要求

要满足 O(log n) 的时间复杂度，需要在 `[left, targetIndex-1]` 和 `[targetIndex+1, right]` 里**继续二分查找**，在左半边里找到第一个 target，在右半边找到最后一个 target

至于怎么找第一个和最后一个，实际上要做的是**改写普通的二分查找**：对于**左半边**，在找到 target 时，看前一个元素是不是也是 target，如果是，就**继续二分查找的循环**，如果不是，就返回它的下标；对于**右半边**，也类似，在找到 target 时，看后一个元素是不是也是 target，如果是，就**继续二分查找的循环**，如果不是，就返回它的下标（注意判断边界溢出问题）

❗题目是要求 O(log n) 的时间复杂度，所以直接怼两次二分查找，2*(log n) = O(log n)，是符合要求的

> ❗❗69 和 367 的边界判定有问题，AC 有水分

#### [69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/)

数学题，太难了😭

数学知识：0 和 1 的平方根是它本身；x 的平方根总小于 x/2（x>4)

二分查找就是不断逼近平方根

#### [367. 有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)

和 69 题一样，二分法解决问题

如果条件判断的时候发现 `middle==num/middle` 且 `num % middle == 0`，就返回 `true`，否则返回 `false` 其他情况下走出循环就返回 `false`

## [27. 移除元素](https://leetcode-cn.com/problems/remove-element/)

题目说明居然很贴心地说明是数组引用，这是我没想到的😶

可以选择每一次发现一个目标元素就把后面的所有元素往前移进行覆盖，就是有点麻烦

tags 给了提示，`two-pointers`，那用双指针

维护两个指针，一个 `i` 用来遍历「原数组」，一个 `j` 用来遍历「返回的数组」

遍历原数组，如果 `nums[i]!=val`，就 `nums[j++]=nums[i++]` 否则就直接 `i++`

因为数组本来就需要遍历，所以 `i` 直接用作循环变量，不需要另外设指针

代码实在太短，忍不住贴上来嗨一下

```c
int removeElement(int *nums, int numsSize, int val)
{
    int j = 0; // 新数组目前遍历到的位置，同时也是新数组的长度

    // 遍历整个数组，如果不等于 val，就采用
    for (int i = 0; i != numsSize; i++)
    {
        if (nums[i] != val)
            nums[j++] = nums[i];
    }
    return j;
}
```

### 相关题目

#### [26. 删除有序数组中的重复项](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)

和 27 题类似，双指针，只是这次要判断的不是目标元素，而是「重复」

因为它是有序的，所以只需要判断「新数组」和「原数组」的当前位（指针指向的值）是不是相等，不相等的不采用即可

要做一个长度判断，要求长度大于等于2，然后先把第一个元素纳入新数组，在这个基础上做循环判断

> 26 和 27 都是双指针，难度也不大，但是在**边界选取**上存在差异，需要注意区分，试了 3 次才 AC

```c
int removeDuplicates(int *nums, int numsSize)
{
    // 长度为 0 和 1 就不判断了，循环的要求是 numsSize >= 2
    if (numsSize < 2)
        return numsSize;
        
    int j = 0; // 新数组目前遍历到的位置，同时也是「新数组的长度 - 1」

    // 遍历整个数组，如果「旧数组」和「新数组」当前位不一样，就采用
    for (int i = 1; i != numsSize; i++)
    {
        if (nums[i] != nums[j])
            nums[++j] = nums[i];
    }
    return j + 1;
}
```



#### [283. 移动零](https://leetcode-cn.com/problems/move-zeroes/)

这题和 27 题比较类似，也是删除目标元素，只是再多做一步，在末尾后面补 0，判断条件比 26 题简单

0 的数量 n = 原数组长度 - 新数组长度，从 nums[numsSize-1] 开始往前写 n 个 0 就行了

```c
void moveZeroes(int *nums, int numsSize)
{
    int j = 0; // 新数组目前遍历到的位置，同时也是新数组的长度

    // 遍历整个数组，如果不等于 0，就采用
    for (int i = 0; i != numsSize; i++)
    {
        if (nums[i] != 0)
            nums[j++] = nums[i];
    }

    // 从 nums[numsSize-1] 开始往前写 0
    for (int i = 0; i != numsSize - j; i++)
    {
        nums[numsSize - 1 - i] = 0;
    }
}
```

> AC 完了看到这个进阶提示：「**进阶：**你能尽量减少完成的操作次数吗？」
>
> 💡确实还能，可以选择**三指针**，直接在发现 0 的时候从数组末尾开始往前写 0
>
> ```c
> void moveZeroes(int *nums, int numsSize)
> {
>     int j = 0;        // 新数组目前遍历到的位置，同时也是新数组的长度
>     int k = numsSize; // 用来写 0 的指针
> 
>     // 遍历整个数组，如果不等于 0，就采用
>     for (int i = 0; i != numsSize; i++)
>     {
>         if (nums[i] != 0)
>             nums[j++] = nums[i];
>         else
>         {
>             nums[--k] = 0;
>         }
>     }
> }
> ```
>
> 写完觉得自己真是个小天才😀，submit ! ，**Wrong Answer**。看着错误提示我才反应过来，我在没遍历完之前就把本来要遍历的数组尾部的数据给写 0 了
>
> 想了很久，确定没有办法实现，溜了
>
> 官方题解的双指针是一个指向 0，一个指向非 0，感觉有点复杂
>
> **如果不要求相对有序**的话，是可以选择把尾部的元素写到 0 的位置的，这种方案倒是可以实现类似上面说的那种思路

#### [844. 比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/)

如果不考虑 `O(n)` 的时间复杂度和 `O(1)` 的空间复杂度，那就直接就写到两个新的数组里，碰到一个 `#` 就指针回退一位

要求空间复杂度 `O(1)` 只能原地比较了，题目没有说不能修改原数组，那就直接上手改它就完事儿了（时间复杂度 `O(m+n)` = `O(n)`）

```c
/**
 * @brief 文本处理
 *
 * 处理字符串中的退格字符 '#'，处理成全字符形式，末尾补上 '\0'
 *
 * @param s 要处理的字符串
 */
void TextProcess(char *s)
{
    int i = 0; // 遍历指针
    int j = 0; // 有效字符指针
    while (s[i])
    {
        // 如果不是 '#'，就采用该字符
        if (s[i] != '#')
        {
            s[j++] = s[i];
        }
        // 如果是 '#'，而且 j 不为 0，就让有效指针回退
        // 不知道会不会有一大堆的 '#'，还是判断一下 0 比较保险
        else if (j != 0)
        {
            j--;
        }
        i++;
    }
    // 处理完了之后在末尾补 0
    s[j] = '\0';
}

bool backspaceCompare(char *s, char *t)
{
    // 直接改动原数组，然后比较
    TextProcess(s);
    TextProcess(t);
    return !strcmp(s, t);
}
```

**其他思路 0**

两个指针，从后往前遍历；两个变量，记录这次需要退格的次数

如果当前字符不是 `#`，退格次数 -1

如果是 `#`，则退格次数 +1

直到退格次数为 0，且当前字符不是 `#` 时，退出循环，得到这次要比较的字符

```c
/**
 * @brief 找到下一个用来比较的字符的下标
 *
 * @param s 要寻找的字符串
 * @param index 开始的下标（从后往前）
 * @return int 找到的下标（没找到就返回 -1，没找到的意思是前面是空的）
 */
int IndexOfNextChar(char *s, int index)
{
    int skipNum = 0; // 退格次数

    while (index >= 0)
    {
        if (s[index] == '#') // 是退格符，记录
        {
            skipNum++;
        }
        else // 如果不是退格符，看一下要不要退格
        {
            if (skipNum == 0)
            {
                // 不需要退格，那找到了
                return index;
            }
            else
            {
                // 需要退格，那就退格
                skipNum--;
            }
        }

        // 继续往前找
        index--;
    }
    // 没找到就返回 -1
    return -1;
}

bool backspaceCompare(char *s, char *t)
{
    // 从后往前遍历

    // 用来比较的指针
    int sIndex = strlen(s) - 1;
    int tIndex = strlen(t) - 1;
    while (true)
    {
        // 找下一个要比较的字符的下标
        sIndex = IndexOfNextChar(s, sIndex);
        tIndex = IndexOfNextChar(t, tIndex);

        if (sIndex == -1 || tIndex == -1) // 如果其中有至少一个前面的部分是空的
        {
            // 如果都是空的，两个字符串相等，返回 ture
            if (sIndex == -1 && tIndex == -1)
                return true;
            else // 否则二者不相等，返回 false
                return false;
        }
        else // 都不为空，开始判断
        {
            // 这两个字符二者不相等，返回 false
            if (s[sIndex] != t[tIndex])
            {
                return false;
            }
            else // 相等则继续找下一个字符
            {
                // 这一位没问题就往前再找一位
                // 不用担心越界，IndexOfNextChar 发现越界会返回 -1
                sIndex--;
                tIndex--;
            }
        }
    }
}
```

因为是从后往前，所以没有回退的问题（时间复杂度 `O(m+n)` = `O(n)`）

**其他思路1**

直接用栈，碰到 `#` 就退栈，最后判断两个栈（不满足空间复杂度要求）



#### [977. 有序数组的平方](https://leetcode-cn.com/problems/squares-of-a-sorted-array/)

数组平方后虽然不再是非递减的，但是是「两边大，中间小」的，所以就可以双指针，指向首尾，向中间递进，取其中大的，写入新数组（从后往前写）

写起来很顺，没啥坑

> 本来应该一遍过的，结果编译出错了三次，因为 `left` 写成 `lfet` 了，vscode 楞是没有一个提示，就挺离谱的，啊？是我关的波浪线啊，那没事了😵

## [209. 长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/)

滑动窗口解法（双指针），维护左右两个指针，使指针域内的数字和 `sum >= target`

可以简单地把窗口滑动的过程分成两部分（有顺序关系）：

1. 右边界右移，使子数组的和符合要求
2. 左边界右移，使子数组的和不再符合要求

然后具体分析在哪些边界的条件下需要判定最小长度 `min_len` 即可

由于每个数都进出窗口一次，故时间复杂度为`O(2n)`=`O(n)`

> 前缀和+二分的没看懂，先跳过

### 相关题目

#### [904. 水果成篮](https://leetcode.cn/problems/fruit-into-baskets/)

需要明确一点，最终找到的那个区间，里面只会有最多两种水果，所以维持一个至多两种水果类型的区间即可

与209类似，同样可以把窗口滑动的过程分成两个部分（有顺序关系）：

1. 右边界右移，使区间内只有两种水果（`right` 尽量大）
2. 左边界右移，使区间内剩下一种水果（类型是 `fruits[right]`）

#### [76. 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/)

维持一个最小子串区间，使区间内至少包含指定数量的目标字符

需要初始化一个键值对/map，记录目标字符及数量

```c
/* 计算 t 中每个字符的数量 */
int value[128] = {0}; // 对应 ASCII 码表，A=65 z=122
for (int i = 0; t[i] != '\0'; i++){
    value[t[i]]++;
}
```

依然是把窗口滑动的过程分成两部分（有顺序关系）：

1. 右边界右移，使区间内包含指定数量的目标字符，然后左边界右移，压缩区间长度至最小
2. 左边界右移一位，使空间不再符合要求

## [59. 螺旋矩阵 II](https://leetcode.cn/problems/spiral-matrix-ii/)

模拟过程。分析怎么确定边界显然很痛苦，不如用一个数组来记录某个位置是否被访问过，以此为依据循环 `right → down → left → up` 即可

### 相关题目

#### [54. 螺旋矩阵](https://leetcode.cn/problems/spiral-matrix/)

和 59 思路类似，59 是写，54 是读

> 实际程序编写中还是出现了一些问题，因为 59 是 n×n，而 54 是 m×n，导致从 59 copy 的代码出错，一开始还没发现，盯了半天才排查出错误，copy 的时候还是需要小心小心再小心😵

# 链表

## [203. 移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/)

注意小心空链表判断

## [707. 设计链表](https://leetcode.cn/problems/design-linked-list/)

体力活

首先，模板给出的结构体是不能直接用的：

```c
typedef struct {

} MyLinkedList;
```

在这个结构里，`next` 的类型不能是 `MyLinkedList*`，因为别名叫 `MyLinkedList` 的结构体压根没有定义完毕，编译器不知道名字叫 `MyLinkedList` 的类型是什么，实际的定义方式如下：

```c
typedef struct MyLinkedList_t{
	int val;
	struct MyLinkedList_t *next;
} MyLinkedList;
```

只实现了带头结点的单链表的版本，双链表懒得写

## [206. 反转链表](https://leetcode.cn/problems/reverse-linked-list/)

用的双指针。看了下递归，我发现我还是是弱智，还是老老实实迭代吧

## [24. 两两交换链表中的节点](https://leetcode.cn/problems/swap-nodes-in-pairs/)

和 206 思路类似，双指针解决。

和 206 的不同之处在于，206 是围绕箭头（指向）为中心，不断前移的「窗口」，窗口大小为 2；而 24 看起来类似，实际上窗口的大小宏观上应该看作 4，因为 `1234→2143`，第一个元素交换后，它的`next` 不再是 `3`，而是 `4`，因此引发的边界判断也需要结合具体代码实现进行处理

> [题解](https://programmercarl.com/0024.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B9.html)里用虚拟头结点的方式好像可以把窗口规模控制在 2，还没有仔细看

## [19. 删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)

双指针（快慢指针），用一个计数器 `i` 记录当前访问的是第几个节点，当 `i==n` 的时候，让一个指针从头节点开始往后遍历（协同主遍历过程）。

分析一下 fast 和 slow 的步进（{1, 2, 3, 4, 5}, n=2, 目标删除 4）：

| 迭代轮次 | fast 指向 | slow 指向 |
| -------- | --------- | --------- |
| 0        | 1         | 1         |
| 1        | 2         | 1         |
| 2        | 3         | 1         |
| 3        | 4         | 1         |
| 4        | 5         | 2         |
| 5        | NULL      | 3         |

显然，当 fast 遍历完毕，`slow->next` 指向的节点即倒数第 n 个节点

从索引上讲，就是维持 fast - slow = n+1

> 没有用**虚拟头结点**，一些情况的判断很 drama，最后因为边界的问题脑子都乱了，如果一开始用上虚拟头结点应该会好很多，索性最终结果是 AC 了，就不改了
>
> 使用虚拟头结点可以显著减少边界情况的处理，为了少死点脑细胞，能用则用

## [面试题 02.07. 链表相交](https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/)

**思路 1**：

创建两个空链表（val 的类型为 node），分别遍历给出的两个链表的所有节点，头插法插入到空链表中。然后用双指针法判断从哪个节点开始两个节点的 val 不同。

**思路 2**：

先看数学结论：若链表 1 长为 a，链表 2 长为 b，且二者相交，相交部分长度为 c。即 a=a'+c，b=b'+c。假设 a>b，则二者差值 d=a-b=a'-b'。

如果链表 1 和链表 2 相交，则 d 为如下区域：

![image-20220608100850639](img/image-20220608100850639.png)

因此，最重要的工作是：**让两个链表右对齐**。然后就可以同步比较两个节点的指针了

再结合实际过程：同步遍历链表 1 和链表 2，显然，当链表 2 遍历完毕后，**链表 1 还差 d 次才能遍历完毕**。这时，再让另外一个指针从链表 1 的头指针开始同步遍历，当链表 1 遍历完毕后，新指针也前进了 d 个位置，这时链表 1 剩余的遍历长度就等于链表 2 的长度，也就是两个链表达成了右对齐。然后逐个比较剩余节点的指针即可

用上三目表达式，整个代码将异常精炼：

```c
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    struct ListNode *link_1 = headA, *link_2 = headB;
    while (link_1 != link_2)
    {
        link_1 = link_1 ? link_1->next : headB;
        link_2 = link_2 ? link_2->next : headA;
    }
    return link_1;
}
```

## [142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)

[题解](https://programmercarl.com/0142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II.html)

最土的办法，遍历的过程中把节点逐一备份（当然用哈希表更好，但是我是用的 C 啊），然后从前往后查这个节点在备份里有没有，有就是它了。显然不满足空间复杂度 `O(1)`

快慢指针法：slow 走一格，fast 走两格，快慢指针会在环里相遇。然后从相遇的位置和头节点同时开始走，他们就会相遇，这个相遇点就是环开始的位置。

所以难点就是数学😭总之就是不会

还有一个有意思的办法：leetcode 在创建链表的时候分配的内存空间是连续的，也就是说，**前一个节点的地址会比后一个结点的地址小**，所以 `        if (p >= p->next) return p->next;` 

# 哈希表

## [242. 有效的字母异位词](https://leetcode.cn/problems/valid-anagram/)

这题判断两个字符串出现次数的方式在 [76. 最小覆盖子串](#76.-最小覆盖子串)中已经用过，而且 76 题还有大小写，这里只有小写，好处理很多，直接定一个大小 26 的数组算每个小写字母出现的字数即可。

### 相关题目

#### [383. 赎金信](https://leetcode.cn/problems/ransom-note/)

和 242 思路一样，白捡一题

就是最简单的哈希，key 就是 index，哈希函数就是 `ransomNote[i] - 'a'`，value 就是对应字母出现次数

#### [49. 字母异位词分组](https://leetcode.cn/problems/group-anagrams/)

直接利用 242 的函数，套两层循环判断两个字符串是否是「字母异位词」，是就放在一组里。

直接用要 242 的函数 要 1800ms，优化一下也只能到 1500ms，看了一下整体逻辑，感觉优化空间不大了，哈希的本质是空间换时间，这种方式看起来空间没省多少，时间倒是慢的要死。不划算啊，还死磕了半天逻辑

#### [438. 找到字符串中所有字母异位词](https://leetcode.cn/problems/find-all-anagrams-in-a-string/)

把 49 改过的 242 的函数再改改，也还能用，这个嵌套层级浅一点，~~效果应该不错~~（当我没说，还是得 1300ms）

做了太多类似的题，已经产生惯性了，实际这题应该用滑动窗口做，因为每滑动一次只会改变一个字母的数据，所以应该用 [76. 最小覆盖子串](#76.-最小覆盖子串)的处理方式看待窗口移动产生的变化，思路有了，心累了，不写了🐟

## [349. 两个数组的交集](https://leetcode.cn/problems/intersection-of-two-arrays/)

**想法一**：最土的办法肯定是直接两层 for 循环了，比较 `nums1[i]` 和 `nums2[j]`。官方给的第一种方法也是这种思想，但是用了哈希表去重，我这才发现，leetcode 引入了哈希表 `uthash.h`，利用它进行去重和查找，效率显然比直接套循环更快。

**想法二**：和想法一类似，先把两个数组做去重和排序，取两个数组各自最小值的更大者作为比较空间的下限，各自最大值的更小者为比较空间的上限，在这个范围内套for循环。逻辑上可行，但是效率上我不知道结果。（当然，直接排序然后用双指针也是可以的）

### 相关题目 [350. 两个数组的交集 II](https://leetcode.cn/problems/intersection-of-two-arrays-ii/)

**想法一**：这题的题目都和 349 很像，整体处理思路没大什么区别，也可以 for 循环嵌套解决，但是因为结果交集存在重复元素，具体细节的处理还是有很多不同的。

区别在于：

1. 不再判断这个数在结果数组中是否存在
2. 为数组2建立一个数组，用于记录某个索引上的数是否之前已被选入结果数组

**想法二**：注意看数字的范围：`0 <= nums1[i], nums2[i] <= 1000`，实际上并不算大，所以可以直接建立两个大小为 1001 的数组，记录 nums1 和 nums2 中每个数出现的次数，若 `record1[i]` 和 `record2[i]` 都不为 0 时，输出二者更小值个数的 `i` 到结果数组

从测试来看，速度比方法一快了很多，因为操作次数明显减少，而由于本身 leetcode OJ 程序运行的开销很大，多出这两个空间基本被忽略了，最小要 6M

> 我看了下最小的 5988 kb 的程序，这王八蛋居然直接把答案写到了 nums1 上面，然后返回 nums1，我 TM ……

**leetcode 官方给出的哈希表法**：遍历第一个数组，记录每个数出现的次数（作为value）。然后遍历第二个数组，如果遍历到的数在哈希表中存在，则输出到结果数组，并让哈希表中的记录次数减 1（`--value` 为 0 则移除）

从结果来看，用上 uthash，内存占用从排名上暴降，属实是空间换时间了，由于规模不大，和法二的运行时间一样，都只有 4ms

**leetcode 官方给出的双指针法**：思路很简单，用 qsort 从小到大排序，如果二者不相等，更小的那个数向前移，如果二者相等，就输出再一起前移

## [202. 快乐数](https://leetcode.cn/problems/happy-number/)

它居然是简单题，属实**快乐不起来**

首先看到 `1 <= n <= 2³¹ - 1` 第一反应是：会不会溢出？实际上是不会的，因为最大也就是十几个 `9²` 相加而已

然后第二点：这不是**模拟**吗？我算不就完事了？仔细想想又不对，如果无限循环，并**不知道怎么退出循环**

然后第三点：这和哈希表是什么关系？没想通。先偷偷看了一眼评论，发现题目其实有高亮提示，如果不能退出，会出现**无限循环**。  
无限循环嘛，那就说明会有重复值，所以只要把每次运算的结果都写到哈希表里就行了，如果表里可以找到，那就可以退出循环了

> 从某种数学玄学上看，如果 20 次都没有跳出循环，这个数肯定不快乐。当然题目不能这么做就是了

看了题解，除了用哈希，还可以用快慢指针，如果发现了环，它就不快乐，环的发现具体思路见 [142. 环形链表 II](#142.-环形链表-II)，总的来说就是龟兔赛跑，快的多跑几圈总会追上慢的

## [1. 两数之和](https://leetcode.cn/problems/two-sum/)

第一题，都做过，暴力解法当然是两层 for 循环

另外的方式就是哈希表法，先让数组的第一个元素加入哈希表，然后从第二个元素开始找，哈希表里有没有和这个元素之和为 target 的  
有就返回这两个数的下标  
没有就把这个数也加入哈希表（key 为值，value 为在数组中的下标）

## [454. 四数相加 II](https://leetcode.cn/problems/4sum-ii/)

暴力破解，四层循环，直接算，**超时**

```c
int fourSumCount(int *nums1, int nums1Size, int *nums2, int nums2Size, int *nums3, int nums3Size, int *nums4, int nums4Size){
    int count = 0;
    /* 4 层循环 */
    for (int index1 = 0; index1 != nums1Size; index1++)
        for (int index2 = 0; index2 != nums2Size; index2++)
            for (int index3 = 0; index3 != nums3Size; index3++)
                for (int index4 = 0; index4 != nums4Size; index4++)
                    if (nums1[index1] + nums2[index2] + nums3[index3] + nums4[index4] == 0)
                        count++;
    return count;
}
```

看了题解，具体方式其实也很简单：**把规模打下去**，暴力破解的时间复杂度是 `i*j*k*l`。  
拆解规模的方式是把 4 个数组对半分成两组（nums1 + nums2 和 nums3 + nums4）），分别计算两个数组各自两个数之和及出现次数，然后再看 `sum1[i]` 和 `sum2[i]` 之和为 0 的总共有多少组，就是最终答案，整体时间复杂度为 `i*j + k*l`（考虑到其他的操作，复杂度带常数倍系数，总之大致是这个规模）

💡注意：如果第一组中有 3 个和为 2 的组合，第二组中有 4 个和为 -2 的组合，则这一对所得的元组数量为 3*4=12 种

## [15. 三数之和](https://leetcode.cn/problems/3sum/)

for 循环嵌套可以得到从位置上而言不重复的三元组，但是数值上三元组是可能重复的：

```
Input
[-1,0,1,2,-1,-4]

Output
[[-1,0,1],[-1,2,-1],[0,1,-1]]

Expected Answer
[[-1,-1,2],[-1,0,1]]
```

那么如何去重，就是一个不太好处理的问题。想到的解决方式是先排序，然后再去重，尝试了之后发现超时了，显然面对较长的数组时，三层 for 循环的耗时太大了。

[题解](https://programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html)给出的方法是先排序，然后用双指针寻找结果，这种方法我不太满意，如果是这样的话，先排序然后for循环嵌套，最后简单去重一下也是可以的，但是看了一下，好像也没有什么其他的办法，就这样吧

```c
int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes){
    if (numsSize < 3){
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    /* 排序 */
    qsort(nums, numsSize, sizeof(int), cmp);

    /* 双指针找结果集 */
    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);
    *returnSize = 0;

    int left;
    int right;
    int sum;

    /* 在[i + 1, numsSize - 1]找 nums[i] 对应的另外两个数 */
    for (int i = 0; i < numsSize - 2; i++){
        /* 由于数组的有序性，如果 nums[i] 已经大于 0，则后面的数字必然大于 0，不需要再找 */
        if (nums[i] > 0)
            break;

        left = i + 1;
        right = numsSize - 1;
        while (left < right){
            sum = nums[i] + nums[left] + nums[right];
            if (sum < 0)
                left++;
            else if (sum > 0)
                right--;
            else // ==0
            {
                result[*returnSize] = (int *)malloc(sizeof(int) * 3);
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnSize)++;
                // break;
                /* 👆不能 break，还有其他的可能，但是需要缩范围 */
                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;

                /* 缩范围 */
                left++;
                right--;
            }
        }

        /* i 前推，避免重复 */
        while (i < numsSize - 3 && nums[i] == nums[i + 1])
            i++;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 3;

    return result;
}
```

最后搞了半天终于 AC 了，感觉还有还是迷迷糊糊的。

> 关于结果集的大小：`int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);` 这里的规模是数组的平方，最开始用的**立方**，发现对于太大的就数组会提示申请内存过多，所以改为了**平方**。
>
> 我也不知道极限情况下的规模是多大😵

## [18. 四数之和](https://leetcode.cn/problems/4sum/)

在[15. 三数之和](#15.-三数之和)的基础上再套一层 for 循环，枚举两个数，然后再用双指针找另外两个数。需要注意的是，这次要求的不是和为 0，而是 target，所以三数之和中做的一些剪枝的操作这里不能再用了。

```c
int comp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes){
    if (numsSize < 4){
        *returnSize = 0;
        return NULL;
    }

    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);
    *returnSize = 0;

    /* 先排序 */
    qsort(nums, numsSize, sizeof(int), comp);

    /* 两层for循环确定两个数 */
    for (int i = 0; i < numsSize - 3; i++){
        for (int j = i + 1; j < numsSize - 2; j++){
            int sum_find = target - (nums[i] + nums[j]);
            /* 双指针找剩下的两个数，其和为 sum_find */
            int left = j + 1, right = numsSize - 1;
            while (left < right){
                int sum = nums[left] + nums[right];
                if (sum == sum_find){
                    result[*returnSize] = (int *)malloc(sizeof(int) * 4);
                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[j];
                    result[*returnSize][2] = nums[left];
                    result[*returnSize][3] = nums[right];
                    (*returnSize)++;

                    /* 缩范围 */
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    /* 定范围 */
                    left++, right--;
                }
                else if (sum < sum_find)
                    left++;
                else // sum > sum_find
                    right--;
            }

            /* 前推，避免重复 */
            while (j < numsSize - 2 && nums[j] == nums[j + 1])
                j++;
        }

        /* 前推，避免重复 */
        while (i < numsSize - 3 && nums[i] == nums[i + 1])
            i++;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 4;

    return result;
}
```

很快就写完调试完 AC 了，但是感觉有点背题的味道了，加上大部分还是 copilot 提示出来的，非常没有实感，很空。

# 字符串

## [344. 反转字符串](https://leetcode.cn/problems/reverse-string/)

0 ↔ size - 1、1 ↔ size - 2、2 ↔ size - 3 …… 没啥好说的

## [541. 反转字符串 II](https://leetcode.cn/problems/reverse-string-ii/)

模拟，具体反转可以直接用 344 的函数

## [剑指 Offer 05. 替换空格](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)

第一个想法：新建一个空数组，逐位读入，碰到空格就写入 `%20`

[题解](https://programmercarl.com/%E5%89%91%E6%8C%87Offer05.%E6%9B%BF%E6%8D%A2%E7%A9%BA%E6%A0%BC.htm)的方法：原地修改，先统计空格的数量，然后扩充数组到需要的长度，然后双指针从后往前逐个移动，并填入 `%20`。看着蛮好，仔细想想不对，C 语言不能这么做，这是访问越界。  
所以对 C 语言来说，统计空格的数量的目的在于避免申请空间过大：`char *ret = (char *)malloc(sizeof(char) * strlen(s) * 3 + 1);` 如果对空间要求敏感，则有必要先遍历一遍空格数量再确定申请的空间大小，当然这显然会在一定程度上影响运行速度（一次遍历而已，影响应该不大？）

## [151. 颠倒字符串中的单词](https://leetcode.cn/problems/reverse-words-in-a-string/)

第一个想法：双指针，从后往前，left 和 right 包裹一个单词，写到另外一个数组。

C 语言修改字符串并不容易，所以没有很好的原地解法

[题解](https://programmercarl.com/0151.%E7%BF%BB%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%87%8C%E7%9A%84%E5%8D%95%E8%AF%8D.html)的方法很巧妙：

"the sky is blue "

- 先处理字符串，去除头尾的空格，每个中间的空格保留一个："the sky is blue"
- 再把整个字符串反转："eulb si yks eht"
- 再把每个单词都反转一次："blue is sky the"

但是这个办法显然不适合 C，因为对字符数组做 trim 的工作用 C 语言手动实现还是比较复杂的。

根据上面的逻辑，我想到一个新办法：把处理空格的步骤和字符处理的步骤结合起来，**遍历处理空格的同时把单词反转**：

"the sky is blue "

- 去除多余空格并反转每个单词："eht yks si eulb"
- 反转整个字符串："blue is sky the"

当然没有解决的问题还是：这不是一个 `O(1)` 空间复杂度的算法，从效率上看，`O(1)` 挺麻烦的，不划算

> 又折腾了几个小时的数组越界问题，憋了半天才解决。这种问题真的太难受了

## [剑指 Offer 58 - II. 左旋转字符串](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

想法一：统一左移 1 位，左移 `k % length` 次，需要一个额外空间（用于暂存），时间复杂度较高

想法二：统一直接左移 `k % length`  位，需要额外 `lenth - (k % length)` 个额外空间，时间复杂度较低  
写到这里反应过来了，实际上是把字符串分成两段：`[0, k % length]`，`[k % length + 1, length - 1]`，然后交换两段的位置即可。

以 s = "abcdefg", k = 2 为例：ab | cdefg → `[0, k]`, `[k + 1, length - 1]`

显然要提高难度，肯定是放在**原地算法**上，[题解](https://programmercarl.com/%E5%89%91%E6%8C%87Offer58-II.%E5%B7%A6%E6%97%8B%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html)给出的方案是：反转第一部分、反转第二部分，整体反转。需要一个额外空间用于交换暂存。

粗略比较一下：

- 原地反转：时间复杂度：2N，空间复杂度：1
- 子串拼接：时间复杂度：N，空间复杂度：N
- 模拟左移：时间复杂度：K*N，空间复杂度：1

## [28. 实现 strStr()](https://leetcode.cn/problems/implement-strstr/)

for 循环嵌套吧，如果第一元素一样，就一个个都试过去。

KMP？看了一半给我整崩溃了，一个 next 数组都折腾半天。

Sunday 算法看起来明显直观很多，总结起来逻辑很直观：  
如果本轮匹配失败，就看窗口外的下一个字符在不在模式串里  
如果不在，直接到下下个字符的位置去匹配；  
如果在，就把模式串里最后一次出现这个字符的位置和下一个字符的位置对齐

看了 Sunday 算法我整个人眼泪流下来，这才是我这种弱智看得懂的算法。

## [459. 重复的子字符串](https://leetcode.cn/problems/repeated-substring-pattern/)

得，报应来了。KMP

不管 KMP 了，数学解法思路如下：

对于字符串 str，如果它可以有由字符串重复构成，  
那么，把两个 str 拼接，即 str + str，然后把这个 str + str 头尾各砍掉一个字符串，必然还能在中间找到一个 str  
（因为有重复的子串，那么子串数量起码是两个：s's'，那么两个 str 就是 s's's's'，破坏掉头尾的 s' 也还是 s-s's's-，中间还有两个子串：s's'

例子："abab" => "abab"+"abab" => "bab"+"aba" （可以找到 "abab"）
