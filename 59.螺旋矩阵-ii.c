/*
 * @lc app=leetcode.cn id=59 lang=c
 *
 * [59] 螺旋矩阵 II
 *
 * https://leetcode.cn/problems/spiral-matrix-ii/description/
 *
 * algorithms
 * Medium (76.26%)
 * Likes:    727
 * Dislikes: 0
 * Total Accepted:    203.5K
 * Total Submissions: 266.9K
 * Testcase Example:  '3'
 *
 * 给你一个正整数 n ，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 3
 * 输出：[[1,2,3],[8,9,4],[7,6,5]]
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 1
 * 输出：[[1]]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 *
 *
 */

// @lc code=start

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **generateMatrix(int n, int *returnSize, int **returnColumnSizes)
{
    *returnSize = n;
    *returnColumnSizes = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        (*returnColumnSizes)[i] = n;
    }

    int **matrix = (int **)malloc(sizeof(int *) * n); // 用于返回的数组
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * n);
    }

    int **visited = (int **)malloc(sizeof(int *) * n); // 记录某个位置是否访问过
    for (int i = 0; i < n; i++)
    {
        visited[i] = (int *)malloc(sizeof(int) * n);
    }

    /* 二维数组初始化（全部置 0） */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    int col = 0; // →
    int row = 0; // ↓
    int count = 1;
    while (1)
    {
        /* 右 */
        while (col < n && visited[row][col] == 0)
        {
            matrix[row][col] = count;
            visited[row][col] = 1;
            col++;

            count++;
            if (count > n * n)
                goto out;
        }
        col--;

        row++;
        /* 下 */
        while (row < n && visited[row][col] == 0)
        {
            matrix[row][col] = count;
            visited[row][col] = 1;
            row++;

            count++;
            if (count > n * n)
                goto out;
        }
        row--;

        col--;
        /* 左 */
        while (col >= 0 && visited[row][col] == 0)
        {
            matrix[row][col] = count;
            visited[row][col] = 1;
            col--;

            count++;
            if (count > n * n)
                goto out;
        }
        col++;


        row--;
        /* 上 */
        while (row >= 0 && visited[row][col] == 0)
        {
            matrix[row][col] = count;
            visited[row][col] = 1;
            row--;

            count++;
            if (count > n * n)
                goto out;
        }
        row++;

        col++;
    }
out:

    /* 释放空间 */
    for (int i = 0; i < n; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return matrix;
}
// @lc code=end
