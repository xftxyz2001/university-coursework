#include <stdio.h>
#include <math.h>

#define SIZE 4

void swapRows(double matrix[SIZE][SIZE], int r1, int r2)
{
    for (int i = 0; i < SIZE; i++)
    {
        double temp = matrix[r1][i];
        matrix[r1][i] = matrix[r2][i];
        matrix[r2][i] = temp;
    }
}

/**
 * 计算矩阵的行列式值
 */
double calculateDeterminant(const double inputMatrix[SIZE][SIZE])
{
    double matrix[SIZE][SIZE];
    // 拷贝矩阵以避免修改原始输入
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = inputMatrix[i][j];
        }
    }

    double det = 1.0;

    for (int i = 0; i < SIZE; i++)
    {
        int maxRow = i;
        for (int j = i; j < SIZE; j++)
        {
            if (fabs(matrix[j][i]) > fabs(matrix[maxRow][i]))
            {
                maxRow = j;
            }
        }

        if (matrix[maxRow][i] == 0)
        {
            return 0;
        }

        if (maxRow != i)
        {
            swapRows(matrix, i, maxRow);
            det *= -1;
        }

        for (int j = i + 1; j < SIZE; j++)
        {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < SIZE; k++)
            {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        det *= matrix[i][i];
    }

    return det;
}

int main(int argc, char const *argv[])
{
    double matrixA[SIZE][SIZE] = {
        {-6, -7, 7, 6},
        {3, 4, 2, 3},
        {-4, -2, 0, 6},
        {1, 7, 8, 3}};

    double matrixB[SIZE][SIZE] = {
        {-3, 4, -2, 5},
        {-4, -4, 4, 2},
        {-3, 6, 1, 6},
        {1, 1, -1, 9}};

    double detA = calculateDeterminant(matrixA);
    double detB = calculateDeterminant(matrixB);

    printf("矩阵 A 的行列式值为：%.2lf\n", detA);
    printf("矩阵 B 的行列式值为：%.2lf\n", detB);

    return 0;
}