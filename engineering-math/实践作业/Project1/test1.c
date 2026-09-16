#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    // 定义一个3x3矩阵
    double matrix[3][3];

    // 提示用户输入矩阵元素
    printf("请输入一个3x3矩阵的元素:\n");
    printf("eg. \n2 5 8\n1 0 1\n1 3 2\n-----\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // 计算行列式的值
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) 
               - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) 
               + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    // 输出行列式的值
    printf("该矩阵的行列式的值为: %lf\n", det);
    return 0;
}
