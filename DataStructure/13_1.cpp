#include<iostream>
#include<cstring>
using namespace std;

struct Matrix
{
    int Rows, Cols, Nums;
    struct
    {
        int row, col, vol;
    }lists[100];
};

void MatrixMul(Matrix&A_Matrix, Matrix&B_Matrix, Matrix&C_Matrix)
{
    C_Matrix.Cols = B_Matrix.Cols; C_Matrix.Rows = A_Matrix.Rows;
    int nnt = 1, NewRow = 0, expt[10000] = { 0 };
    for (int i = 1; i <= A_Matrix.Nums; i++)
    {
        if (NewRow != A_Matrix.lists[i].row)
        {
            for (int j = 1; j <= B_Matrix.Cols; j++)
            {
                if (expt[j] != 0)
                {
                    C_Matrix.lists[nnt].col = j;
                    C_Matrix.lists[nnt].vol = expt[j];
                    C_Matrix.lists[nnt].row = NewRow;
                    nnt++;
                }
            }
            memset(expt, 0, sizeof(expt));
            NewRow = A_Matrix.lists[i].row;
        }
        for (int j = 1; j <= B_Matrix.Nums; j++)
            if (A_Matrix.lists[i].col == B_Matrix.lists[j].row)
                expt[B_Matrix.lists[j].col] += A_Matrix.lists[i].vol*B_Matrix.lists[j].vol;
    }
    for (int i = 1; i <= B_Matrix.Cols; i++)
    {
        if (expt[i] != 0)
        {
            C_Matrix.lists[nnt].col = i;
            C_Matrix.lists[nnt].vol = expt[i];
            C_Matrix.lists[nnt].row = NewRow;
            nnt++;
        }
    }
    C_Matrix.Nums = nnt - 1;
}

int main()
{
    Matrix A_Matrix, B_Matrix, C_Matrix;
    scanf("%d", &A_Matrix.Rows);
    scanf("%d", &A_Matrix.Cols);
    scanf("%d", &A_Matrix.Nums);
    for (int i = 1; i <= A_Matrix.Nums; i++)
        scanf("%d %d %d", &A_Matrix.lists[i].row, &A_Matrix.lists[i].col, &A_Matrix.lists[i].vol);
    scanf("%d", &B_Matrix.Rows);
    scanf("%d", &B_Matrix.Cols);
    scanf("%d", &B_Matrix.Nums);
    for (int i = 1; i <= B_Matrix.Nums; i++)
        scanf("%d %d %d", &B_Matrix.lists[i].row, &B_Matrix.lists[i].col, &B_Matrix.lists[i].vol);
    MatrixMul(A_Matrix, B_Matrix, C_Matrix);
    printf("%d\n%d\n%d\n", C_Matrix.Rows, C_Matrix.Cols, C_Matrix.Nums);
    for (int i = 1; i <= C_Matrix.Nums; i++)
        printf("%d,%d,%d\n", C_Matrix.lists[i].row, C_Matrix.lists[i].col, C_Matrix.lists[i].vol);

    return 0;
}
