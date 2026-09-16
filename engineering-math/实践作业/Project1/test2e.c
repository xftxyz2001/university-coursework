#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 函数声明
double calculateDeterminant(int n, double **matrix);
int eliminate(double **matrix, int n); // 修改为返回交换次数
void swapRows(double **matrix, int row1, int row2, int n);

int main(int argc, char const *argv[])
{
    int n;
    printf("请输入矩阵的阶数: ");
    scanf("%d", &n);

    // 动态分配二维数组
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }

    // 输入矩阵元素
    printf("请输入矩阵的元素:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("matrix[%d][%d] = ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }

    // 计算行列式的值
    double det = calculateDeterminant(n, matrix);
    printf("该矩阵的行列式的值为: %lf\n", det);

    // 释放内存
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

double calculateDeterminant(int n, double **matrix)
{
    double det = 1.0;
    int rowSwaps = eliminate(matrix, n); // 获取行交换次数

    for (int i = 0; i < n; i++)
    {
        det *= matrix[i][i];
    }

    if (rowSwaps % 2 != 0) // 如果交换次数为奇数，改变行列式符号
    {
        det *= -1;
    }

    return det;
}

int eliminate(double **matrix, int n)
{
    int rowSwaps = 0; // 记录行交换次数

    for (int k = 0; k < n - 1; k++)
    {
        // 寻找主元（绝对值最大的行）
        int maxRow = k;
        for (int i = k + 1; i < n; i++)
        {
            if (fabs(matrix[i][k]) > fabs(matrix[maxRow][k]))
            {
                maxRow = i;
            }
        }

        // 如果主元为0，则行列式为0
        if (fabs(matrix[maxRow][k]) < 1e-9)
        {
            return rowSwaps; // 提前返回交换次数
        }

        // 交换当前行和主元所在行
        if (maxRow != k)
        {
            swapRows(matrix, k, maxRow, n);
            rowSwaps++; // 增加交换次数
        }

        // 消去下方所有行的当前列元素
        for (int i = k + 1; i < n; i++)
        {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < n; j++)
            {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }

    return rowSwaps; // 返回总交换次数
}

void swapRows(double **matrix, int row1, int row2, int n)
{
    double *temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}