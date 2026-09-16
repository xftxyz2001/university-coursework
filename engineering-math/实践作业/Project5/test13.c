#include <stdio.h>
#include <math.h>

#define ROW 3
#define COL 3

void printVectors(double vecs[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        printf("[");
        for (int j = 0; j < COL; j++)
            printf(" %.4lf ", vecs[i][j]);
        printf("]\n");
    }
}

double dot(double *v1, double *v2, int len)
{
    double sum = 0;
    for (int i = 0; i < len; i++)
        sum += v1[i] * v2[i];
    return sum;
}

void gramSchmidt(double input[ROW][COL], double output[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            output[i][j] = input[i][j];
        for (int j = 0; j < i; j++)
        {
            double proj = dot(input[i], output[j], COL) / dot(output[j], output[j], COL);
            for (int k = 0; k < COL; k++)
                output[i][k] -= proj * output[j][k];
        }
    }
}

int main(int argc, char const *argv[])
{

    double mat[ROW][COL] = {
        {1, 1, 1},
        {1, 0, 2},
        {1, 2, 3}};

    double ortho[ROW][COL];
    printf("原始向量：\n");
    printVectors(mat);

    gramSchmidt(mat, ortho);

    printf("\n正交化后的向量：\n");
    printVectors(ortho);

    return 0;
}
