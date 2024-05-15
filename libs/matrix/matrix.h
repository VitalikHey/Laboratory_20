#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct matrix {
    int **values; // элементы матрицы
    size_t nRows; // количество рядов
    size_t nCols; // количество столбцов
} matrix;

// размещает в динамической памяти матрицу размером nRows на nCols.
// Возвращает матрицу.
matrix getMemMatrix(size_t nRows, size_t nCols);

// заполняет матрицу нулями
void matrixFillingZeros(matrix *m, size_t row, size_t col);

// возвращает значение ’истина’, если матрицы m1 и m2 равны,
// ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2);

// возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, int nRows, int nCols);

#endif
