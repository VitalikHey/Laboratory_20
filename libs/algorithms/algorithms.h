#ifndef LABORATORY_20_ALGORITHMS_H
#define LABORATORY_20_ALGORITHMS_H

#include <stdio.h>
#include <limits.h>
#include <conio.h>
#include <signal.h>
#include <string.h>

#include "../matrix/matrix.h"
#include "../domain/domain.h"
#include "../node/node.h"
#include "../vector/vector.h"

void firstTaskAlgorithm(matrix *m, size_t countRequests, size_t *requestsArray[]);

void secondTaskAlgorithm(matrix m, matrix *newM, size_t rows, size_t cols);

void thirdTaskAlgorithm(matrix *m, size_t size);

void fourthTaskAlgorithm(domain *array, size_t size);

void fifthTaskAlgorithm(matrix m, size_t rows, size_t cols, size_t *result);

void sixthTaskAlgorithm(const char *s, size_t length, char *result,
                        size_t *resultLength);

void seventhTaskAlgorithm(int array[], int lengthArray);

void eighthTaskAlgorithm(const char *s, size_t length,
                         const size_t indexes[], char *newS);

void ninthTaskAlgorithm(int numsArray[], size_t lengthArray, int controlNum,
                        char *firstFileName, char *secondFileName, vector *v);

void tenthTaskAlgorithm(char *fileName, size_t countOutputLines, char *text);

#endif //LABORATORY_20_ALGORITHMS_H
