#include "algorithms.h"
#include "signal.h"
#include <unistd.h>

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

FILE* openFile(char *fileName, char *action){
    FILE *file = fopen(fileName, action);
    if (file == NULL) {
        printf("Error opening the file\n");
        exit(1);
    }
    return file;
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

void fillingCalcMatrix(matrix m, matrix *calcMatrix, size_t rows, size_t cols){
    for (size_t indRow = 0; indRow < rows; indRow++){
        for (size_t indCol = 0; indCol < cols; indCol++){
            if (m.values[indRow][indCol] == 1){
                if (indRow != 0){
                    calcMatrix->values[indRow][indCol] =
                            calcMatrix->values[indRow - 1][indCol] + 1;
                }
                else{
                    calcMatrix->values[indRow][indCol] = 1;
                }
            } else {
                calcMatrix->values[indRow][indCol] = 0;
            }
        }
    }
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



void fifthTaskAlgorithm(matrix m, size_t rows, size_t cols, size_t *result){
    matrix calcMatrix = getMemMatrix(rows, cols);
    fillingCalcMatrix(m, &calcMatrix, rows, cols);

    size_t calcResult = 0;
    for (size_t indCol = 0; indCol < cols; indCol++){
        for (size_t indRow = 0; indRow < rows; indRow++){
            for (size_t indK = indCol + 1; indK < cols + 1; indK++){
                int min = calcMatrix.values[indRow][indCol];
                for (size_t indFromColToK = indCol; indFromColToK < indK;
                     indFromColToK++){
                    if (calcMatrix.values[indRow][indFromColToK] < min){
                        min = calcMatrix.values[indRow][indFromColToK];
                    }
                }
                calcResult += min;
            }
        }
    }

    *result = calcResult;
}

void sixthTaskAlgorithm(const char *s, size_t length, char *result,
                        size_t *resultLength){
    char buffer[10];
    size_t bufferLength = 0;
    size_t calcResultLength = 0;

    char num = '1';
    for (size_t ind = 0; ind < length; ind++) {
        buffer[bufferLength++] = num++;
        if (s[ind] == 'I') {
            while (bufferLength > 0)
                result[calcResultLength++] = buffer[--bufferLength];
        }
    }

    buffer[bufferLength++] = num;
    while (bufferLength > 0)
        result[calcResultLength++] = buffer[--bufferLength];

    result[calcResultLength] = '\0';
    *resultLength = calcResultLength;
}

int searchMaxInd(int array[], int start, int end) {
    int maxNum = array[start];
    int maxInd = start;

    for (int i = start + 1; i <= end; i++) {
        if (array[i] > maxNum) {
            maxNum = array[i];
            maxInd = i;
        }
    }

    return maxInd;
}

void buildNodes(node *currentNode, int array[], int startInd, int endInd, bool isLeft) {
    if (startInd > endInd) {
        return;
    }

    int maxInd = searchMaxInd(array, startInd, endInd);
    node *newNode = createNode(array[maxInd]);

    if (isLeft) {
        currentNode->left = newNode;
    } else {
        currentNode->right = newNode;
    }

    buildNodes(newNode, array, startInd, maxInd - 1, true);
    buildNodes(newNode, array, maxInd + 1, endInd, false);
}

void breadthFirstTraversal(node *root) {
    if (root == NULL) {
        return;
    }

    node *queue[100];  // Используем массив для имитации очереди
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        node *current = queue[front++];
        printf("%d ", current->key);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

void seventhTaskAlgorithm(int array[], int lengthArray) {
    if (lengthArray == 0) {
        return;
    }

    int maxNumInd = searchMaxInd(array, 0, lengthArray - 1);
    node *root = createNode(array[maxNumInd]);
    printf("%d ", array[maxNumInd]);
    buildNodes(root, array, 0, maxNumInd - 1, true);
    buildNodes(root, array, maxNumInd + 1, lengthArray - 1, false);
    printf("\n");

    breadthFirstTraversal(root);
    printf("\n");
}

void eighthTaskAlgorithm(const char *s, size_t length,
                         const size_t indexes[], char *newS){
    for (size_t ind = 0; ind < length; ind++){
        newS[ind] = s[indexes[ind]];
    }
    newS[length] = '\0';
}


void fillingFile(int numsArray[], size_t lengthArray, char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", fileName);
        return;
    }

    for (size_t ind = 0; ind < lengthArray; ind++) {
        fprintf(file, "%d ", numsArray[ind]);
    }

    fclose(file);
}

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int controlNum, char *wFileName) {
    FILE *rFile = fopen(rFileName, "r");
    if (rFile == NULL) {
        fprintf(stderr, "Error opening file %s\n", rFileName);
        return;
    }

    FILE *wFile = fopen(wFileName, "w");
    if (wFile == NULL) {
        fprintf(stderr, "Error opening file %s\n", wFileName);
        fclose(rFile);
        return;
    }

    int num;
    while (fscanf(rFile, "%d", &num) == 1) {
        if (num < controlNum) {
            v->data[v->size++] = num;
            fprintf(wFile, "%d ", num);
        }
    }

    fclose(rFile);
    fclose(wFile);
}

void shrinkToFit(vector *v) {
    int *newData = (int *)malloc(sizeof(int) * v->size);
    for (size_t i = 0; i < v->size; i++) {
        newData[i] = v->data[i];
    }

    free(v->data);
    v->data = newData;
    v->capacity = v->size;
}

void ninthTaskAlgorithm(int numsArray[], size_t lengthArray, int controlNum, char *firstFileName, char *secondFileName, vector *v) {
    fillingFile(numsArray, lengthArray, firstFileName);
    readingNumsFilteringAndWriting(v, firstFileName, controlNum, secondFileName);
    shrinkToFit(v);
}

void fillingFileWithText(char *fileName, char *text){
    FILE *file = openFile(fileName, "w");
    fprintf(file, "%s", text);
    fclose(file);
}


void signalHandler(int signum) {
    if (signum == SIGINT) {
        printf("\nCtrl + C pressed. Exiting...\n");
        exit(0);
    }
}

void tenthTaskAlgorithm(char *fileName, size_t countOutputLines, char *text) {
    fillingFileWithText(fileName, text);

    FILE *file = openFile(fileName, "r");

    char line[127];
    size_t count = 0;

    signal(SIGINT, signalHandler);

    while (fgets(line, 127, file) != NULL) {
        printf("%s", line);
        count++;

        if (count == countOutputLines){
            printf("Press Ctrl + C\n");
            pause();
        }
    }
}