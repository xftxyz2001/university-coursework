#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 4 // 至少4阶

void printMatrix(double mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%8.3lf ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int rank(double mat[N][N])
{
    int rank = N;
    for (int row = 0; row < rank; row++)
    {
        if (fabs(mat[row][row]) > 1e-6)
        {
            for (int col = 0; col < N; col++)
            {
                if (col != row)
                {
                    double mult = mat[col][row] / mat[row][row];
                    for (int i = 0; i < rank; i++)
                        mat[col][i] -= mult * mat[row][i];
                }
            }
        }
        else
        {
            int reduce = 1;
            for (int i = row + 1; i < N; i++)
            {
                if (fabs(mat[i][row]) > 1e-6)
                {
                    for (int j = 0; j < rank; j++)
                    {
                        double temp = mat[row][j];
                        mat[row][j] = mat[i][j];
                        mat[i][j] = temp;
                    }
                    reduce = 0;
                    break;
                }
            }
            if (reduce)
            {
                rank--;
                for (int i = 0; i < N; i++)
                    mat[i][row] = mat[i][rank];
            }
            row--;
        }
    }
    return rank;
}

int main(int argc, char const *argv[])
{

    double mat[N][N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = rand() % 10;

    printf("原始矩阵：\n");
    printMatrix(mat);

    int r = rank(mat);
    printf("矩阵的秩为：%d\n", r);

    return 0;
}
