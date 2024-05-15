#include "matrix.h"

matrix getMemMatrix(size_t nRows, size_t nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}


void matrixFillingZeros(matrix *m, size_t row, size_t col){
    for (size_t indRow = 0; indRow < row; indRow++){
        for (size_t indCol = 0; indCol < col; indCol++){
            m->values[indRow][indCol] = 0;
        }
    }
}


bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols){
        return false;
    }

    for (int indRow = 0; indRow < m1->nRows; indRow++){
        int resCheck = memcmp(m1->values[indRow],m2->values[indRow],
                              sizeof(int) * m1->nCols);
        if (resCheck){
            return false;
        }
    }

    return true;
}


matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}
