#include <stdio.h>
#include <math.h>

#define SIZE 3 // 三元非齐次方程组

void swapRows(double mat[SIZE][SIZE + 1], int r1, int r2)
{
    for (int i = 0; i <= SIZE; i++)
    {
        double temp = mat[r1][i];
        mat[r1][i] = mat[r2][i];
        mat[r2][i] = temp;
    }
}

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(0)); // 初始化随机种子

    double mat[SIZE][SIZE + 1];
    // 随机生成矩阵元素
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE + 1; j++)
        {
            mat[i][j] = rand() % 100; // 随机值范围 0-99
        }
    }

    // 打印生成的矩阵（可选）
    printf("随机生成的矩阵：\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j <= SIZE; j++)
        {
            printf("%.2lf\t", mat[i][j]);
        }
        printf("\n");
    }

    double det = 1.0;
    int swapCount = 0;

    // 高斯消元化为上三角矩阵
    for (int i = 0; i < SIZE; i++)
    {
        // 寻找主元行
        int maxRow = i;
        for (int j = i; j < SIZE; j++)
        {
            if (fabs(mat[j][i]) > fabs(mat[maxRow][i]))
            {
                maxRow = j;
            }
        }
        if (mat[maxRow][i] == 0)
        {
            printf("方程组无唯一解！\n");
            return 0;
        }
        if (maxRow != i)
        {
            swapRows(mat, i, maxRow);
            det *= -1;
            swapCount++;
        }
        // 消元
        for (int j = i + 1; j < SIZE; j++)
        {
            double factor = mat[j][i] / mat[i][i];
            for (int k = i; k <= SIZE; k++)
            {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }

    // 回代求解
    double x[SIZE];
    for (int i = SIZE - 1; i >= 0; i--)
    {
        x[i] = mat[i][SIZE];
        for (int j = i + 1; j < SIZE; j++)
        {
            x[i] -= mat[i][j] * x[j];
        }
        x[i] /= mat[i][i];
    }

    printf("方程组的解为：\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("x%d = %.2lf\n", i + 1, x[i]);
    }

    return 0;
}