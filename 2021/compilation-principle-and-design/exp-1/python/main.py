import numpy as np

DIMENSION = 100

matrix_a = np.zeros((DIMENSION, DIMENSION))
matrix_b = np.zeros((DIMENSION, DIMENSION))
matrix_c = np.zeros((DIMENSION, DIMENSION))

for i in range(DIMENSION):
    for j in range(DIMENSION):
        matrix_a[i][j] = i+j
        matrix_b[j][i] = i*j

for i in range(DIMENSION):
    for j in range(DIMENSION):
        for k in range(DIMENSION):
            matrix_c[i][j] += matrix_a[i][k]*matrix_b[k][j]
