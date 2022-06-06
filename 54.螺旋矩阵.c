/*
 * @lc app=leetcode.cn id=54 lang=c
 *
 * [54] 螺旋矩阵
 *
 * https://leetcode.cn/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (48.80%)
 * Likes:    1113
 * Dislikes: 0
 * Total Accepted:    268.7K
 * Total Submissions: 550.7K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * 输出：[1,2,3,6,9,8,7,4,5]
 *
 *
 * 示例 2：
 *
 *
 * 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * 输出：[1,2,3,4,8,12,11,10,9,5,6,7]
 *
 *
 *
 *
 * 提示：
 *
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1
 * -100
 *
 *
 */

// @lc code=start

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize)
{
    int m = matrixSize;
    int n = matrixColSize[0];
    *returnSize = m * n;

    /* 创建一个 m*n 的二维数组，保存访问记录 */
    int **visited = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        visited[i] = (int *)malloc(sizeof(int) * n);
    }

    /* 数组初始化 */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = 0;
        }
    }

    int *ret = (int *)malloc(sizeof(int) * (m * n)); // 要返回的数组
    int row = 0;
    int col = 0;
    int count = 1;

    while (1)
    {
        /* 右 */
        while (col < n && visited[row][col] == 0)
        {
            ret[count - 1] = matrix[row][col];
            visited[row][col] = 1;
            col++;

            count++;
            if (count > m * n)
                goto out;
        }
        col--;

        row++;
        /* 下 */
        while (row < m && visited[row][col] == 0)
        {
            ret[count - 1] = matrix[row][col];
            visited[row][col] = 1;
            row++;

            count++;
            if (count > m * n)
                goto out;
        }
        row--;

        col--;
        /* 左 */
        while (col >= 0 && visited[row][col] == 0)
        {
            ret[count - 1] = matrix[row][col];
            visited[row][col] = 1;
            col--;

            count++;
            if (count > m * n)
                goto out;
        }
        col++;

        row--;
        /* 上 */
        while (row >= 0 && visited[row][col] == 0)
        {
            ret[count - 1] = matrix[row][col];
            visited[row][col] = 1;
            row--;

            count++;
            if (count > m * n)
                goto out;
        }
        row++;

        col++;
    }
out:

    /* 释放空间 */
    for (int i = 0; i < m; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return ret;
}
// @lc code=end
