#include<cstdio>
#include<cstdlib>
#include<memory.h>

struct Matrix {
    int column;
    int row;
    int size;
    struct {
        int column;
        int row;
        int value;
    } element_list[110];
};

int main() {
    Matrix matrix[3];
    for (int i = 0; i < 2; i++) {
        scanf("%d%d%d", &matrix[i].column, &matrix[i].row, &matrix[i].size);
        for (int j = 1; j <= matrix[i].size; j++) {
            scanf("%d%d%d", &matrix[i].element_list[j].column, &matrix[i].element_list[j].row,
                  &matrix[i].element_list[j].value);
        }
    }
    matrix[2].column = matrix[0].column;
    matrix[2].row = matrix[1].row;
    int sum = 0, current_col = 0, tmp_buffer[10000] = {0};
    for (int i = 1; i <= matrix[0].size; i++) {
        if (current_col != matrix[0].element_list[i].column) {
            for (int j = 1; j <= matrix[1].row; j++) {
                if (tmp_buffer[j] != 0) {
                    matrix[2].element_list[sum].column = current_col;
                    matrix[2].element_list[sum].row = j;
                    matrix[2].element_list[sum].value = tmp_buffer[j];
                    sum++;
                }
            }
            current_col = matrix[0].element_list[i].column;
            memset(tmp_buffer, 0, (matrix[1].row + 1) * sizeof(int));
        }
        for (int j = 1; j <= matrix[1].size; j++) {
            if (matrix[0].element_list[i].row == matrix[1].element_list[j].column) {
                tmp_buffer[matrix[1].element_list[j].row] +=
                        matrix[0].element_list[i].value * matrix[1].element_list[j].value;
            }
        }
    }
    for (int i = 1; i <= matrix[1].row; i++) {
        if (tmp_buffer[i] != 0) {
            matrix[2].element_list[sum].column = current_col;
            matrix[2].element_list[sum].row = i;
            matrix[2].element_list[sum].value = tmp_buffer[i];
            sum++;
        }
    }
    matrix[2].size = sum;
    printf("%d\n%d\n%d\n", matrix[2].column, matrix[2].row, matrix[2].size);
    for (int i = 0; i < sum; i++) {
        printf("%d,%d,%d\n", matrix[2].element_list[i].column, matrix[2].element_list[i].row,
               matrix[2].element_list[i].value);
    }
    return 0;
}