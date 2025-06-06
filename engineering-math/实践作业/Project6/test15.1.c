/* 验证出生频率趋近 1/2 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMS 1000000 // 模拟次数

int main()
{
    long boys = 0, girls = 0;
    srand((unsigned)time(NULL));
    for (long i = 0; i < SIMS; ++i)
    {
        if (rand() & 1)
            boys++; // 随机最低位模拟 0/1
        else
            girls++;
    }
    printf("模拟次数: %ld\n男孩: %ld (%.5f)\n女孩: %ld (%.5f)\n",
           SIMS,
           boys, (double)boys / SIMS,
           girls, (double)girls / SIMS);
    return 0;
}