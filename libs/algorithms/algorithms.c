#include "algorithms.h"

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
