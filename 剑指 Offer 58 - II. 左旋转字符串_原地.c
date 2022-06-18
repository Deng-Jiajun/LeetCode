// [剑指 Offer 58 - II. 左旋转字符串]
// (https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

void reverseString(char *s, int sSize)
{
    int left = 0;
    int right = sSize - 1;
    char temp;
    while (left < right)
    {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++, right--;
    }
}
char *reverseLeftWords(char *s, int k)
{
    /* 旋转：s[0, k % length - 1] 和 s[k % length, length - 1] */
    reverseString(s + 0, k % strlen(s));
    reverseString(s + k % strlen(s), strlen(s) - k % strlen(s));

    /* 整体旋转 */
    reverseString(s, strlen(s));
    return s;
}
