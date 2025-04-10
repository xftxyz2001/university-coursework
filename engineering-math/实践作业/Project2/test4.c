#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 矩阵转置函数
void transposeMatrix(int **matrix, int **transpose, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}

// 打印矩阵函数
void printMatrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int rows, cols;
    printf("请输入矩阵的行数: ");
    scanf("%d", &rows);
    printf("请输入矩阵的列数: ");
    scanf("%d", &cols);

    // 动态分配内存
    int **matrix = (int **)malloc(rows * sizeof(int *));
    int **transpose = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    for (int i = 0; i < cols; i++)
    {
        transpose[i] = (int *)malloc(rows * sizeof(int));
    }

    // 生成随机矩阵
    srand(time(NULL));
    printf("原始矩阵:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 10; // 随机数在0到9之间
        }
    }
    printMatrix(matrix, rows, cols); // 调用打印矩阵函数

    // 转置矩阵
    transposeMatrix(matrix, transpose, rows, cols);

    // 打印转置后的矩阵
    printf("转置后的矩阵:\n");
    printMatrix(transpose, cols, rows); // 调用打印矩阵函数

    // 释放分配的内存
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    for (int i = 0; i < cols; i++)
    {
        free(transpose[i]);
    }
    free(transpose);

    return 0;
}