/* 甲乙出差问题 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIMS 1000000

int main()
{
    const double pA = 0.80;    // 甲出差概率 P(A)
    const double pB_A = 0.20;  // 甲出差时乙出差 P(B|A)
    const double pB_nA = 0.90; // 甲不出差时乙出差 P(B|?A)

    // (1) 全概率公式
    double pB = pB_A * pA + pB_nA * (1 - pA);
    printf("理论 P(B) = %.4f\n", pB);

    // (2) 贝叶斯公式
    double pA_B = pB_A * pA / pB;
    printf("理论 P(A|B) = %.4f\n", pA_B);

    // Monte?Carlo 验证
    long cntA = 0, cntB = 0, cntAB = 0;
    srand((unsigned)time(NULL));
    for (long i = 0; i < SIMS; ++i)
    {
        int A = (rand() < pA * RAND_MAX);
        int B;
        if (A)
            B = (rand() < pB_A * RAND_MAX);
        else
            B = (rand() < pB_nA * RAND_MAX);

        if (A)
            cntA++;
        if (B)
            cntB++;
        if (A && B)
            cntAB++;
    }
    printf("仿真  P(B) = %.4f\n", (double)cntB / SIMS);
    printf("仿真  P(A|B) = %.4f\n", (double)cntAB / cntB);
    return 0;
}