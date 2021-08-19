#include <stdio.h>

#define DIMENSION 100

int matrix_a[DIMENSION][DIMENSION] = {0};
int matrix_b[DIMENSION][DIMENSION] = {0};
int matrix_c[DIMENSION][DIMENSION] = {0};

int main()
{
    // Initialize matrixes
    for (int i = 0; i < DIMENSION; i++)
        for (int j = 0; j < DIMENSION; j++)
        {
            matrix_a[i][j] = i + j;
            matrix_b[j][i] = i * j;
        }
    // Multiply two matrixes
    for (int i = 0; i < DIMENSION; i++)
        for (int j = 0; j < DIMENSION; j++)
            for (int k = 0; k < DIMENSION; k++)
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
    return 0;
}