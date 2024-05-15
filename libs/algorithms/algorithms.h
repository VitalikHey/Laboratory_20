#ifndef LABORATORY_20_ALGORITHMS_H
#define LABORATORY_20_ALGORITHMS_H

#include <stdio.h>
#include <limits.h>
#include <conio.h>

#include "../matrix/matrix.h"
#include "../domain/domain.h"

// алгоритм решения первой задачки
void firstTaskAlgorithm(matrix *m, size_t countRequests, size_t *requestsArray[]);

void secondTaskAlgorithm(matrix m, matrix *newM, size_t rows, size_t cols);

#endif //LABORATORY_20_ALGORITHMS_H
