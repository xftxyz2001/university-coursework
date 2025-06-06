/* 癌症普查可靠性 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIMS 1000000

int main()
{
    const double pC = 0.005;     // 先验 P(C)
    const double pPos_C = 0.95;  // 真阳性 = 1 - 假阴性
    const double pPos_nC = 0.05; // 假阳性

    // Bayes 理论阳性后的患病概率 (PPV)
    double pPos = pPos_C * pC + pPos_nC * (1 - pC);
    double pC_Pos = pPos_C * pC / pPos;
    printf("理论  P(C|阳性) = %.4f\n", pC_Pos);

    // Monte?Carlo
    long cntC = 0, cntPos = 0, cntPosC = 0;
    srand((unsigned)time(NULL));
    for (long i = 0; i < SIMS; ++i)
    {
        int C = rand() < pC * RAND_MAX; // 是否真患癌
        int Pos;
        if (C)
            Pos = rand() < pPos_C * RAND_MAX;
        else
            Pos = rand() < pPos_nC * RAND_MAX;

        if (C)
            cntC++;
        if (Pos)
            cntPos++;
        if (Pos && C)
            cntPosC++;
    }
    printf("仿真  P(C|阳性) = %.4f\n", (double)cntPosC / cntPos);

    if (pC_Pos < 0.5)
        printf("结论: 阳性预测值仅 %.2f%%, 不宜用于大规模普查。\n", pC_Pos * 100);
    else
        printf("结论: 可考虑用于普查。\n");
    return 0;
}