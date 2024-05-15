#include "algorithms.h"

bool isIndex(size_t rows, size_t cols, int indRow, int indCol){
    if (indRow > -1 && indRow < rows && indCol > -1 && indCol < cols){
        return true;
    }

    return false;
}

bool searchNumFromArray(const size_t array[], size_t length, size_t num){
    for (size_t ind = 0; ind < length; ind++){
        if (num == array[ind]){
            return true;
        }
    }

    return false;
}


size_t searchDomainInResults(const domain results[], size_t size, char *s){
    for (size_t ind = 0; ind < size; ind++){
        if (strcmp(results[ind].name, s) == 0){
            return ind;
        }
    }

    return size;
}

void handlerDotPrtNotNull(domain *array, size_t ind, char *dotPtr,
                          domain results[], size_t *sizeResult){
    strcpy(array[ind].name, dotPtr + 1);
    size_t pos = searchDomainInResults(results, *sizeResult,
                                       array[ind].name);
    if (pos == *sizeResult){
        results[*sizeResult] = array[ind];
        *sizeResult += 1;
    } else{
        results[pos].visits += array[ind].visits;
    }
}


void outputResultDomains(domain *results, size_t size){
    for (size_t ind = 0; ind < size; ind++){
        printf("%ld %s\n", results[ind].visits, results[ind].name);
    }
}

int sortedNumsCompare(const void * firstNum, const void * secondNum){
    return ( *(int*)firstNum - *(int*)secondNum );
}

int cellResultByPosition(matrix m, int indRow, int indCol,
                         size_t countNeighbors){
    return ((m.values[indRow][indCol] == 1 && (countNeighbors == 2
                                               || countNeighbors == 3)) ||
            (m.values[indRow][indCol] == 0 && countNeighbors == 3));
}


size_t calculateCountNeighbors(matrix m, int rowInd, int colInd,
                               size_t rows, size_t cols){
    size_t countNeighbors = 0;
    for (int indRowMath = rowInd - 1; indRowMath < rowInd + 2;
         indRowMath++){
        for (int indColMath = colInd - 1; indColMath < colInd + 2;
             indColMath++){
            if (isIndex(rows, cols, indRowMath, indColMath) &&
                m.values[indRowMath][indColMath] &&
                (rowInd != indRowMath || colInd != indColMath)){
                countNeighbors++;
            }
        }
    }

    return countNeighbors;
}

void fillingNumFrameSorted(int *array, matrix m, size_t indRow, size_t indCol){
    size_t arrayInd = 0;
    for (size_t mIndRow = indRow - 1; mIndRow < indRow + 2; mIndRow++){
        for(size_t mIndCol = indCol - 1; mIndCol < indCol + 2; mIndCol++){
            if (mIndRow != indRow || mIndCol != indCol){
                array[arrayInd++] = m.values[mIndRow][mIndCol];
            }
        }
    }

    qsort(array, 8, sizeof(int), sortedNumsCompare);
}


void firstTaskAlgorithm(matrix *m, size_t countRequests, size_t *requestsArray[]){
    size_t row1, col1, row2, col2;
    for (size_t request = 0; request < countRequests; request++){
        row1 = requestsArray[request][0];
        col1 = requestsArray[request][1];
        row2 = requestsArray[request][2];
        col2 = requestsArray[request][3];
        for (size_t indRow = row1; indRow <= row2; indRow++){
            for (size_t indCol = col1; indCol <= col2; indCol++){
                m->values[indRow][indCol]++;
            }
        }
    }
}

void secondTaskAlgorithm(matrix m, matrix *newM, size_t rows, size_t cols){
    for (int indRow = 0; indRow < rows; indRow++){
        for (int indCol = 0; indCol < cols; indCol++){
            size_t countNeighbors = calculateCountNeighbors(m, indRow, indCol,
                                                            rows, cols);

            newM->values[indRow][indCol] = cellResultByPosition(m, indRow,
                                                                indCol,
                                                                countNeighbors);
        }
    }
}

void thirdTaskAlgorithm(matrix *m, size_t size){
    int frame[8];
    for (size_t indRow = 1; indRow < size - 1; indRow++){
        for(size_t indCol = 1; indCol < size - 1; indCol++){
            fillingNumFrameSorted(frame, *m, indRow, indCol);
            int median = (frame[3] + frame[4]) / 2;
            m->values[indRow][indCol] = median;
        }
    }
}

void fourthTaskAlgorithm(domain array[], size_t size){
    size_t closeIndexes[size];
    size_t countClose = 0;
    domain results[200];
    size_t sizeResult = 0;

    for (size_t ind = 0; ind < size; ind++){
        results[sizeResult++] = array[ind];
    }

    while(countClose != size){
        for (size_t ind = 0; ind < size; ind++){
            if (!searchNumFromArray(closeIndexes, countClose, ind)){
                char *dotPtr = strchr(array[ind].name, '.');

                if (dotPtr != NULL){
                    handlerDotPrtNotNull(array, ind, dotPtr,
                                         results, &sizeResult);
                } else{
                    closeIndexes[countClose++] = ind;
                }
            }
        }
    }

    outputResultDomains(results, sizeResult);
}