public class Matrix {
    private static int DIMENSION = 100;

    public static void main(String[] args) {
        int[][] matrixA = new int[DIMENSION][DIMENSION];
        int[][] matrixB = new int[DIMENSION][DIMENSION];
        int[][] matrixC = new int[DIMENSION][DIMENSION];

        for (int i = 0; i < DIMENSION; i++)
            for (int j = 0; j < DIMENSION; j++) {
                matrixA[i][j] = i + j;
                matrixB[j][i] = i * j;
            }

        for (int i = 0; i < DIMENSION; i++)
            for (int j = 0; j < DIMENSION; j++)
                for (int k = 0; k < DIMENSION; k++)
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
        return;
    }
}