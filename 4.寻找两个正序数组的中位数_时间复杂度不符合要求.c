/*
 * @lc app=leetcode.cn id=4 lang=c
 *
 * [4] 寻找两个正序数组的中位数
 *
 * https://leetcode-cn.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (41.12%)
 * Likes:    5081
 * Dislikes: 0
 * Total Accepted:    627.8K
 * Total Submissions: 1.5M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 *
 * 算法的时间复杂度应该为 O(log (m+n)) 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [1,3], nums2 = [2]
 * 输出：2.00000
 * 解释：合并数组 = [1,2,3] ，中位数 2
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [1,2], nums2 = [3,4]
 * 输出：2.50000
 * 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 *
 *
 *
 *
 *
 *
 * 提示：
 *
 *
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -10^6 <= nums1[i], nums2[i] <= 10^6
 *
 *
 */

// @lc code=start

/**
 * 测试用例
[1,3]
[2]
[1,2]
[3,4]
[1,2,3]
[3,4,5,6,7,8,9]
[3,4,5,6,7,8,9]
[1,2,3]
[3,4,5]
[1,2,3]
[]
[1,2,3]
[3,4,5]
[]
[1,2]
[-1,3]
[1,2]
[1,2,3,4]
 */
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    // 中位数分为两种情况：两个数组的总长度为奇数、两个数组的总长度为偶数
    // 奇数的情况下，为中间的那个数，偶数时为中间两个数相加除2

    // 维护两个分别指向 nums1 和 nums2 的指针
    // 两两比较，每次确定一位数的位置
    // 总长为奇数的情况下，第 (nums1Size+nums2Size)/2 + 1 次比较时得到中位数（更小的那个
    // * 总长为偶数的情况下，第 (nums1Size+nums2Size)/2 次比较时的两个数取平均，得到中位数 ❌这个说法是错的，有可能中间的两个数在同一个数组里❗
    // 总长为偶数的情况下，第 (nums1Size+nums2Size)/2 次与第 (nums1Size+nums2Size)/2 +1 次比较时的更小的那两个数取平均，得到中位数
    // 如果在到那次关键比较之前，某一个数组已经遍历完了，那两个数组就已经排序完毕，根据位置在剩余的部分里找中位数即可
    // ! 时间复杂度 (m+n)/2，不符合要求

    // 单独处理一下空数组
    if (nums1Size == 0 && nums2Size == 0)
        return 0;

    // 数组1为空，到数组2找中位数
    if (nums1Size == 0)
    {
        // 奇数个数字
        if (nums2Size % 2 == 1)
            return nums2[nums2Size / 2];
        // 偶数个数字
        else
            return (double)(nums2[nums2Size / 2 - 1] + nums2[nums2Size / 2]) / 2;
    }
    // 数组2为空，到数组1找中位数
    if (nums2Size == 0)
    {
        // 奇数个数字
        if (nums1Size % 2 == 1)
            return nums1[nums1Size / 2];
        // 偶数个数字
        else
            return (double)(nums1[nums1Size / 2 - 1] + nums1[nums1Size / 2]) / 2;
    }

    // 两个指针(记下标就够了)
    int index1 = 0;
    int index2 = 0;

    // 比较次数统计
    int count = 0;

    // 总数是不是奇数
    bool isOdd;
    if ((nums1Size + nums2Size) % 2 == 1)
        isOdd = true;
    else
        isOdd = false;

    // 比较次数的关键结点
    int keyCount;

    if (isOdd)
        keyCount = (nums1Size + nums2Size) / 2 + 1;
    else
        keyCount = (nums1Size + nums2Size) / 2;

    // 遍历，直到其中一个数组到达尾部
    while (index1 != nums1Size && index2 != nums2Size)
    {
        // 比较次数 +1
        count++;

        // 到达关键比较次数，进行特殊处理
        if (count == keyCount)
        {
            // 总数为奇数，更小的数就是中位数
            if (isOdd)
            {
                return nums1[index1] < nums2[index2] ? nums1[index1] : nums2[index2];
            }
            // 总数为偶数，需要进行两次比较，得到两个中位数
            else
            {
                int num1;
                int num2;

                // 先确定第一个数是多少
                if (nums1[index1] <= nums2[index2])
                {
                    num1 = nums1[index1];
                    num2 = nums2[index2]; // !num2 *有可能*是第二个中位数
                    index1++;
                }
                else
                {
                    num1 = nums2[index2];
                    num2 = nums1[index1]; // !num2 *有可能*是第二个中位数
                    index2++;
                }

                //  !注意，以下论断的前提是当前已经到达了关键的比较次数
                // 如果一个数组空了，那第二个数肯定在另一个数组那儿（就是刚比较的另一个数num2）
                // 不可能两个数组都空，在这之前必然找到了中位数（如果两个数组都只有1个值，返回这两个数的平均值也没错）
                if (index1 == nums1Size || index2 == nums2Size)
                {
                    return (double)(num1 + num2) / 2;
                }
                // 如果两个数都不为空，继续比较，找到第二个更小的数字，求平均
                else
                {
                    // 至于那个数出现在那个数组里，已经不需要关心了
                    num2 = nums1[index1] < nums2[index2] ? nums1[index1] : nums2[index2];
                    return (double)(num1 + num2) / 2;
                }

                // return (double)(nums1[index1] + nums2[index2]) / 2;
            }
        }

        // 更小的那个数组，把指针往后移
        if (nums1[index1] <= nums2[index2])
            index1++;
        else
            index2++;
    }

    // 在剩下的部分里，找中位数
    // 不存在两个数组都遍历完的情况（在此之前肯定找到中位数了）
    // 最极端的情况是一个数组全部遍历完，另一个数组 index=0
    // 可以肯定的一点是剩下的部分数量大于已遍历的（nums2Size - index2 > count）

    // 目前的情形相当于在两个数组里找退化为了在一个数组里找
    // 数组总长 nums1Size+nums2Size，关键结点*下标*是 keyCount-1(相对于大数组)

    // 看一下是哪个数组没遍历完
    if (index1 == nums1Size)
    {
        // 不管奇偶，都要把坐标往前推 numsSize 个位置
        if (isOdd)
            return nums2[keyCount - 1 - nums1Size];
        else
            return (double)(nums2[keyCount - 1 - nums1Size] + nums2[keyCount - 1 - nums1Size + 1]) / 2;
    }
    else if (index2 == nums2Size)
    {
        // 不管奇偶，都要把坐标往前推 numsSize 个位置
        if (isOdd)
            return nums1[keyCount - 1 - nums2Size];
        else
            return (double)(nums1[keyCount - 1 - nums2Size] + nums1[keyCount - 1 - nums2Size + 1]) / 2;
    }

    return -1;
}
// @lc code=end
