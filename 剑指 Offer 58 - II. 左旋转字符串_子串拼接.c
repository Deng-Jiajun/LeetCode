// [剑指 Offer 58 - II. 左旋转字符串]
// (https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

char *reverseLeftWords(char *s, int k)
{
    char *ret = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    memset(ret, 0, sizeof(char) * (strlen(s) + 1));

    /** 两段交换位置：
     * s[k % length, length - 1]     =>  ret[0, k % length - 1]
     * s[0, k % length - 1]          =>  ret[k % length, length - 1]
     */
    strncpy(ret, s + (k % strlen(s)), strlen(s) - k % strlen(s));
    strncpy(ret + (strlen(s) - k % strlen(s)), s, k % strlen(s));
    return ret;
}
