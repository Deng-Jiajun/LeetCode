// [剑指 Offer 05. 替换空格]
// (https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)

char *replaceSpace(char *s)
{
    char *ret = (char *)malloc(sizeof(char) * strlen(s) * 3 + 1);

    int index_s = 0;
    int index_ret = 0;

    while (s[index_s])
    {
        if (s[index_s] == ' ')
        {
            ret[index_ret++] = '%';
            ret[index_ret++] = '2';
            ret[index_ret++] = '0';
        }
        else
        {
            ret[index_ret++] = s[index_s];
        }
        index_s++;
    }
    ret[index_ret] = '\0';
    return ret;
}