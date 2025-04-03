#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculateDeterminant(int n, double a[], double b[], double c[]);

int main()
{
    int n;
    printf("请输入矩阵的阶数: ");
    scanf("%d", &n);

    double *a = (double *)malloc((n - 1) * sizeof(double));
    double *b = (double *)malloc(n * sizeof(double));
    double *c = (double *)malloc((n - 1) * sizeof(double));

    printf("请输入主对角线上的元素:\n");
    for (int i = 0; i < n; i++)
    {
        printf("b[%d] = ", i + 1);
        scanf("%lf", &b[i]);
    }

    printf("请输入上对角线上的元素:\n");
    for (int i = 0; i < n - 1; i++)
    {
        printf("a[%d] = ", i + 1);
        scanf("%lf", &a[i]);
    }

    printf("请输入下对角线上的元素:\n");
    for (int i = 0; i < n - 1; i++)
    {
        printf("c[%d] = ", i + 1);
        scanf("%lf", &c[i]);
    }

    double det = calculateDeterminant(n, a, b, c);
    printf("该三对角矩阵的行列式的值为: %lf\n", det);

    return 0;
}

double calculateDeterminant(int n, double a[], double b[], double c[])
{
    if (n == 1)
    {
        return b[0];
    }

    double *alpha = (double *)malloc((n - 1) * sizeof(double));
    double *beta = (double *)malloc((n - 1) * sizeof(double));

    alpha[0] = b[0];
    beta[0] = c[0] / alpha[0];

    for (int i = 1; i < n - 1; i++)
    {
        alpha[i] = b[i] - a[i] * beta[i - 1];
        beta[i] = c[i] / alpha[i];
    }

    double det = b[n - 1] - a[n - 1] * beta[n - 2];

    free(alpha);
    free(beta);

    return det;
}
