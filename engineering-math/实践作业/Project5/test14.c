#include <stdio.h>
#include <math.h>

#define N 3
#define EPS 1e-6

void printMatrix(double A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%8.4lf ", A[i][j]);
        printf("\n");
    }
}

int isSymmetric(double A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return 0;
    return 1;
}

void jacobi(double A[N][N], double eigenvalues[N]) {
    double V[N][N] = {0};
    for (int i = 0; i < N; i++) V[i][i] = 1;
    while (1) {
        int p = 0, q = 1;
        double max = fabs(A[p][q]);
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                if (fabs(A[i][j]) > max) {
                    max = fabs(A[i][j]);
                    p = i; q = j;
                }
        if (max < EPS) break;
        double theta = 0.5 * atan2(2*A[p][q], A[q][q]-A[p][p]);
        double c = cos(theta), s = sin(theta);
        double App = c*c*A[p][p] - 2*s*c*A[p][q] + s*s*A[q][q];
        double Aqq = s*s*A[p][p] + 2*s*c*A[p][q] + c*c*A[q][q];
        A[p][p] = App;
        A[q][q] = Aqq;
        A[p][q] = A[q][p] = 0;
        for (int j = 0; j < N; j++) {
            if (j != p && j != q) {
                double Apj = c*A[p][j] - s*A[q][j];
                double Aqj = s*A[p][j] + c*A[q][j];
                A[p][j] = A[j][p] = Apj;
                A[q][j] = A[j][q] = Aqj;
            }
        }
    }
    for (int i = 0; i < N; i++)
        eigenvalues[i] = A[i][i];
}

int main(int argc, char const *argv[])
{

    double A[N][N] = {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };

    printf("输入矩阵：\n");
    printMatrix(A);

    if (!isSymmetric(A)) {
        printf("该矩阵不是对称矩阵！\n");
        return 0;
    }

    double eigs[N];
    jacobi(A, eigs);

    printf("\n矩阵的特征值为：\n");
    for (int i = 0; i < N; i++)
        printf("%.6lf\n", eigs[i]);

    return 0;
}
