#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 3

void generate_matrix(int matrix[SIZE][SIZE]);
void print_matrix(int matrix[SIZE][SIZE]);
void add_matrices(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]);
int determinant(int matrix[SIZE][SIZE]);
void inverse_matrix(int matrix[SIZE][SIZE], double inv[SIZE][SIZE]);
double determinant_double(double matrix[SIZE][SIZE]);

int main()
{
    srand(time(NULL));
    int A[SIZE][SIZE], B[SIZE][SIZE], sum[SIZE][SIZE];
    int detA, detB, detSum;
    double invA[SIZE][SIZE];
    double detInvA;

    // Generate A until it's invertible
    do
    {
        generate_matrix(A);
    } while (determinant(A) == 0);

    generate_matrix(B); // B can be singular

    printf("Matrix A:\n");
    print_matrix(A);
    printf("Matrix B:\n");
    print_matrix(B);

    // Part 1: A + B
    add_matrices(A, B, sum);
    printf("A + B:\n");
    print_matrix(sum);

    // Part 2: det(A+B) vs det(A) + det(B)
    detSum = determinant(sum);
    detA = determinant(A);
    detB = determinant(B);
    printf("det(A+B) = %d\n", detSum);
    printf("det(A) + det(B) = %d\n", detA + detB);
    printf("det(A+B) == det(A)+det(B)? %s\n", detSum == detA + detB ? "Yes" : "No");

    // Part 3: det(A+B) vs det(A)*det(B)
    printf("det(A)*det(B) = %d\n", detA * detB);
    printf("det(A+B) == det(A)*det(B)? %s\n", detSum == detA * detB ? "Yes" : "No");

    // Part 4: det(A⁻¹) vs 1/det(A)
    inverse_matrix(A, invA);
    detInvA = determinant_double(invA);
    printf("det(A⁻¹) = %.5f\n", detInvA);
    printf("1/det(A) = %.5f\n", 1.0 / detA);
    printf("det(A⁻¹) == 1/det(A)? %s\n", fabs(detInvA - 1.0 / detA) < 1e-6 ? "Yes" : "No");

    return 0;
}

void generate_matrix(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = rand() % 10 + 1; // Random integers 1-10
        }
    }
}

void print_matrix(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

int determinant(int matrix[SIZE][SIZE])
{
    int a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
    int d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
    int g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

void inverse_matrix(int matrix[SIZE][SIZE], double inv[SIZE][SIZE])
{
    int det = determinant(matrix);
    double inv_det = 1.0 / det;

    // Compute cofactor matrix
    double cofactor[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int sign = (i + j) % 2 == 0 ? 1 : -1;
            int submatrix[2][2];
            int sub_i = 0;
            for (int row = 0; row < SIZE; row++)
            {
                if (row == i)
                    continue;
                int sub_j = 0;
                for (int col = 0; col < SIZE; col++)
                {
                    if (col == j)
                        continue;
                    submatrix[sub_i][sub_j] = matrix[row][col];
                    sub_j++;
                }
                sub_i++;
            }
            int minor_det = submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0];
            cofactor[i][j] = sign * minor_det;
        }
    }

    // Transpose cofactor to get adjugate
    double adjugate[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            adjugate[i][j] = cofactor[j][i];
        }
    }

    // Multiply by inverse determinant
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            inv[i][j] = adjugate[i][j] * inv_det;
        }
    }
}

double determinant_double(double matrix[SIZE][SIZE])
{
    double a = matrix[0][0], b = matrix[0][1], c = matrix[0][2];
    double d = matrix[1][0], e = matrix[1][1], f = matrix[1][2];
    double g = matrix[2][0], h = matrix[2][1], i = matrix[2][2];
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}
