#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

void generate_matrix(int matrix[SIZE][SIZE]);
void print_matrix(int matrix[SIZE][SIZE]);
void matrix_add(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]);
void matrix_subtract(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]);
void matrix_multiply(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE]);
void create_identity_matrix(int I[SIZE][SIZE]);
int check_zero(int matrix[SIZE][SIZE]);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int A[SIZE][SIZE], I[SIZE][SIZE], temp1[SIZE][SIZE], temp2[SIZE][SIZE];
    int left[SIZE][SIZE], right[SIZE][SIZE], diff[SIZE][SIZE];

    create_identity_matrix(I);

    for (int trial = 0; trial < 3; trial++)
    {
        generate_matrix(A);
        printf("Trial %d: \nMatrix A: \n", trial + 1);
        print_matrix(A);

        // Compute (A + I) and (A - I)
        matrix_add(A, I, temp1);      // A + I
        matrix_subtract(A, I, temp2); // A - I

        // Compute (A + I)(A - I)
        matrix_multiply(temp1, temp2, left);

        // Compute A^2 - I
        matrix_multiply(A, A, right);
        matrix_subtract(right, I, right);

        // Compute difference: left - right
        matrix_subtract(left, right, diff);

        printf("Verification: (A+I)(A-I) - (A^2 - I) = \n");
        print_matrix(diff);

        if (check_zero(diff))
        {
            printf("Result: Equation holds.\n");
        }
        else
        {
            printf("Result: Equation does not hold.\n");
        }
    }
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

void matrix_add(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_subtract(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void matrix_multiply(int A[SIZE][SIZE], int B[SIZE][SIZE], int result[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void create_identity_matrix(int I[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            I[i][j] = (i == j) ? 1 : 0;
        }
    }
}

int check_zero(int matrix[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (matrix[i][j] != 0)
                return 0;
        }
    }
    return 1;
}
