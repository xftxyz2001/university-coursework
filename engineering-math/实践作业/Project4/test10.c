#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 4

// 创建随机矩阵
void createMatrix(double matrix[][N], int n);

// 输出
void printMatrix(double matrix[][N], int n);

// 交换两行
void swapRows(double matrix[][2 * N], int row1, int row2, int n);

// 高斯消元法求逆矩阵
void gaussJordanElimination(double matrix[][2 * N], int n);

int main()
{
    double A[N][N];
    createMatrix(A, N);
    printf("原始矩阵:\n");
    printMatrix(A, N);

    // 创建单位矩阵
    double I[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            I[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // 将矩阵与单位矩阵合并为增广矩阵
    double augmented[N][2 * N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            augmented[i][j] = A[i][j];
        }
        for (int j = N; j < 2 * N; j++)
        {
            augmented[i][j] = I[i][j - N];
        }
    }

    // 使用高斯消元法对矩阵进行消元
    gaussJordanElimination(augmented, N);

    // 提取逆矩阵部分
    double inverse[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inverse[i][j] = augmented[i][N + j];
        }
    }

    printf("逆矩阵:\n");
    printMatrix(inverse, N);

    return 0;
}

// 随机生成矩阵元素
void createMatrix(double matrix[][N], int n)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = (double)(rand() % 1000) / 100.0;
        }
    }
}

// 输出
void printMatrix(double matrix[][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 交换矩阵中的两行
void swapRows(double matrix[][2 * N], int row1, int row2, int n)
{
    for (int j = 0; j < 2 * N; j++)
    {
        double temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

// 高斯消元法
void gaussJordanElimination(double matrix[][2 * N], int n)
{
    for (int col = 0; col < n; col++)
    {
        // 寻找主元所在的行，选择绝对值最大的行以减少误差
        int pivotRow = col;
        double maxVal = fabs(matrix[col][col]);
        for (int i = col + 1; i < n; i++)
        {
            if (fabs(matrix[i][col]) > maxVal)
            {
                maxVal = fabs(matrix[i][col]);
                pivotRow = i;
            }
        }

        // 如果主元所在行不在当前行，则交换行
        if (pivotRow != col)
        {
            swapRows(matrix, pivotRow, col, n);
        }

        // 检查矩阵是否奇异（不可逆）
        if (fabs(matrix[col][col]) < 1e-12)
        {
            printf("矩阵是奇异的，无法求逆。\n");
            exit(EXIT_FAILURE);
        }

        // 归一化主元行
        double pivot = matrix[col][col];
        for (int j = 0; j < 2 * N; j++)
        {
            matrix[col][j] /= pivot;
        }

        // 消去其他行
        for (int i = 0; i < n; i++)
        {
            if (i != col)
            {
                double factor = matrix[i][col];
                for (int j = 0; j < 2 * N; j++)
                {
                    matrix[i][j] -= factor * matrix[col][j];
                }
            }
        }
    }
}