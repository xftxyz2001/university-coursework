#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数声明
void inputMatrix(int matrix[3][3]);
int sumDiagonal(int matrix[3][3]);
void multiplyMatrices(int A[3][3], int B[3][3], int result[3][3]);
void printMatrix(int matrix[3][3]);
int main(int argc, char const *argv[])
{

    int matrix1[3][3];
    int matrix2[3][3];
    int result[3][3] = {0};

    printf("请输入第一个3x3矩阵:\n");
    inputMatrix(matrix1);

    printf("请输入第二个3x3矩阵:\n");
    inputMatrix(matrix2);

    // 计算第一个矩阵的对角线元素之和
    int diagonalSum = sumDiagonal(matrix1);
    printf("第一个矩阵的对角线元素之和: %d\n", diagonalSum);

    // 检查矩阵是否可以相乘
    if (sizeof(matrix1[0]) / sizeof(matrix1[0][0]) == sizeof(matrix2) / sizeof(matrix2[0]))
    {
        multiplyMatrices(matrix1, matrix2, result);
        printf("矩阵相乘结果:\n");
        printMatrix(result);
    }
    else
    {
        printf("矩阵无法相乘，因为第一个矩阵的列数不等于第二个矩阵的行数。\n");
    }

    return 0;
}

// 输入一个3x3矩阵
void inputMatrix(int matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("输入第%d行第%d列的元素: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// 计算3x3矩阵对角线元素之和
int sumDiagonal(int matrix[3][3])
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += matrix[i][i];
    }
    return sum;
}

// 矩阵相乘
void multiplyMatrices(int A[3][3], int B[3][3], int result[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 打印矩阵
void printMatrix(int matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
