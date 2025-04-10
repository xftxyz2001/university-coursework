#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 矩阵加法
void addMatrices(int rows, int cols, int **mat1, int **mat2, int **result)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// 矩阵乘法
void multiplyMatrices(int rows1, int cols1, int **mat1, int rows2, int cols2, int **mat2, int **result)
{
    if (cols1 != rows2)
    {
        return;
    }

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++)
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// 矩阵转置
void transposeMatrix(int rows, int cols, int **mat, int **result)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[j][i] = mat[i][j];
        }
    }
}

// 矩阵生成
int **generateMatrix(int rows, int cols)
{
    int **mat = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        mat[i] = (int *)malloc(cols * sizeof(int));
    }
    return mat;
}

// 矩阵初始化
void initMatrix(int rows, int cols, int **mat, int random)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = random ? rand() % 100 : 0;
        }
    }
}

// 矩阵打印
void printMatrix(int rows, int cols, int **mat)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL));
    // 随机生成三个3乘3的矩阵
    int rows = 3, cols = 3;
    int **A = generateMatrix(rows, cols);
    initMatrix(rows, cols, A, 1);
    int **B = generateMatrix(rows, cols);
    initMatrix(rows, cols, B, 1);
    int **C = generateMatrix(rows, cols);
    initMatrix(rows, cols, C, 1);

    printf("A:\n");
    printMatrix(rows, cols, A);
    printf("B:\n");
    printMatrix(rows, cols, B);
    printf("C:\n");
    printMatrix(rows, cols, C);

    // A(B+C)=AB+AC
    int **B_C = generateMatrix(rows, cols);
    initMatrix(rows, cols, B_C, 0);
    addMatrices(rows, cols, A, B, B_C);

    int **A_B_C = generateMatrix(rows, cols);
    multiplyMatrices(rows, cols, A, rows, cols, B_C, A_B_C);

    int **AB = generateMatrix(rows, cols);
    initMatrix(rows, cols, AB, 0);
    multiplyMatrices(rows, cols, A, rows, cols, B, AB);

    int **AC = generateMatrix(rows, cols);
    initMatrix(rows, cols, AC, 0);
    multiplyMatrices(rows, cols, A, rows, cols, C, AC);

    int **AB_AC = generateMatrix(rows, cols);
    initMatrix(rows, cols, AB_AC, 0);
    addMatrices(rows, cols, AB, AC, AB_AC);

    printf("A(B+C):\n");
    printMatrix(rows, cols, A_B_C);
    printf("AB+AC:\n");
    printMatrix(rows, cols, AB_AC);

    // (AB)C=A(BC)
    int **ABC = generateMatrix(rows, cols);
    initMatrix(rows, cols, ABC, 0);
    multiplyMatrices(rows, cols, AB, rows, cols, C, ABC);

    int **BC = generateMatrix(rows, cols);
    initMatrix(rows, cols, BC, 0);
    multiplyMatrices(rows, cols, B, rows, cols, C, BC);

    int **ABC2 = generateMatrix(rows, cols);
    initMatrix(rows, cols, ABC2, 0);
    multiplyMatrices(rows, cols, A, rows, cols, BC, ABC2);

    printf("(AB)C:\n");
    printMatrix(rows, cols, ABC);
    printf("A(BC):\n");
    printMatrix(rows, cols, ABC2);

    // (ABC)^T=(C^T)(B^T)(A^T)
    int **ABC_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, ABC_T, 0);
    transposeMatrix(rows, cols, ABC, ABC_T);

    int **C_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, C_T, 0);
    transposeMatrix(rows, cols, C, C_T);

    int **B_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, B_T, 0);
    transposeMatrix(rows, cols, B, B_T);

    int **A_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, A_T, 0);
    transposeMatrix(rows, cols, A, A_T);

    int **C_T_B_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, C_T_B_T, 0);
    multiplyMatrices(rows, cols, C_T, rows, cols, B_T, C_T_B_T);

    int **C_T_B_T_A_T = generateMatrix(rows, cols);
    initMatrix(rows, cols, C_T_B_T_A_T, 0);
    multiplyMatrices(rows, cols, C_T_B_T, rows, cols, A_T, C_T_B_T_A_T);

    printf("(ABC)^T:\n");
    printMatrix(rows, cols, ABC_T);
    printf("(C^T)(B^T)(A^T):\n");
    printMatrix(rows, cols, C_T_B_T_A_T);

    return 0;
}
