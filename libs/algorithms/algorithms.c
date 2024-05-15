#include "algorithms.h"

bool isIndex(size_t rows, size_t cols, int indRow, int indCol){
    if (indRow > -1 && indRow < rows && indCol > -1 && indCol < cols){
        return true;
    }

    return false;
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
