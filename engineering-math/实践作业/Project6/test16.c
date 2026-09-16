/* coin_poisson.c —— 二项/泊松对比与误差 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 计算阶乘 (k<=20) */
double fact(int k)
{
    static double memo[21] = {0};
    if (k == 0 || k == 1)
        return 1.0;
    if (memo[k])
        return memo[k];
    return memo[k] = k * fact(k - 1);
}

/* 二项系数 C(n,k) 使用 loggamma 防溢出 */
long double comb(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
    long double res = 1;
    for (int i = 1; i <= k; i++)
        res = res * (n - k + i) / i;
    return res;
}

int main()
{
    int n;
    double p;
    printf("输入抛硬币次数 n 和 成功概率 p (如 100 0.05): ");
    if (scanf("%d %lf", &n, &p) != 2)
        return 0;
    double lambda = n * p;
    printf("λ = np = %.4f\n", lambda);
    printf("k\tP_bin\t\tP_poi\t\trel_error(%%)\n");
    for (int k = 0; k <= 10; k++)
    {
        long double Pbin = comb(n, k) * pow(p, k) * pow(1 - p, n - k);
        long double Ppoi = pow(lambda, k) * exp(-lambda) / fact(k);
        long double err = fabsl(Pbin - Ppoi) / Pbin * 100;
        printf("%d\t%Le\t%Le\t%.3Lf\n", k, Pbin, Ppoi, err);
    }
    return 0;
}