#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 函数声明
double determinant(double **matrix, int n);
double **minor(double **matrix, int n, int row, int col);
double **adjoint(double **matrix, int n);

int main()
{
    int n;
    printf("请输入矩阵的阶数: ");
    scanf("%d", &n);

    // 动态分配矩阵内存
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }

    printf("请输入矩阵的元素:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    double **adj = adjoint(matrix, n);

    printf("伴随矩阵为:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%lf ", adj[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for (int i = 0; i < n; ++i)
    {
        free(matrix[i]);
        free(adj[i]);
    }
    free(matrix);
    free(adj);

    return 0;
}

// 计算行列式
double determinant(double **matrix, int n)
{
    if (n == 1)
        return matrix[0][0];
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    double det = 0;
    for (int i = 0; i < n; ++i)
    {
        double **m = minor(matrix, n, 0, i);
        det += pow(-1, i) * matrix[0][i] * determinant(m, n - 1);
        // 释放子式的内存
        for (int j = 0; j < n - 1; ++j)
        {
            free(m[j]);
        }
        free(m);
    }
    return det;
}

// 计算代数余子式矩阵
double **minor(double **matrix, int n, int row, int col)
{
    double **m = (double **)malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; ++i)
    {
        m[i] = (double *)malloc((n - 1) * sizeof(double));
    }

    int r = 0, c = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i == row)
            continue;
        c = 0;
        for (int j = 0; j < n; ++j)
        {
            if (j == col)
                continue;
            m[r][c] = matrix[i][j];
            ++c;
        }
        ++r;
    }
    return m;
}

// 计算伴随矩阵
double **adjoint(double **matrix, int n)
{
    double **adj = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; ++i)
    {
        adj[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            double **m = minor(matrix, n, i, j);
            adj[j][i] = pow(-1, i + j) * determinant(m, n - 1);
            // 释放子式的内存
            for (int k = 0; k < n - 1; ++k)
            {
                free(m[k]);
            }
            free(m);
        }
    }
    return adj;
}