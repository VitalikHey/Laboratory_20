#include "tests.h"


void testFirstTask(){
    size_t size = 3;
    matrix got = getMemMatrix(size, size);
    matrixFillingZeros(&got, size, size);
    size_t countRequests = 2;
    size_t firstRequest[4] = {1, 1, 2, 2};
    size_t secondRequest[4] = {0, 0, 1, 1};
    size_t *requests[2] = {firstRequest, secondRequest};

    firstTaskAlgorithm(&got, countRequests, requests);

    matrix expected = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    1, 2, 1,
                    0, 1, 1
            }, 3, 3
    );

    assert(areTwoMatricesEqual(&got, &expected));
}


void testSecondTask(){
    size_t rows = 4;
    size_t cols = 3;
    matrix start = createMatrixFromArray(
            (int[]) {
                    0, 1, 0,
                    0, 0, 1,
                    1, 1, 1,
                    0, 0, 0
            }, 4, 3
    );

    matrix got = getMemMatrix(rows, cols);
    secondTaskAlgorithm(start, &got, rows, cols);

    matrix expected = createMatrixFromArray(
            (int[]) {
                    0, 0, 0,
                    1, 0, 1,
                    0, 1, 1,
                    0, 1, 0
            }, 4, 3
    );
    assert(areTwoMatricesEqual(&got, &expected));
}


void testThirdTask(){
    size_t size = 3;
    matrix got = createMatrixFromArray(
            (int[]) {
                10, 20, 30,
                25, 35, 45,
                15, 25, 35
            }, 3, 3
    );
    thirdTaskAlgorithm(&got, size);

    matrix expected = createMatrixFromArray(
            (int[]) {
                10, 20, 30,
                25, 25, 45,
                15, 25, 35
            }, 3, 3
    );
    assert(areTwoMatricesEqual(&got, &expected));
}

// не писал автотесты под вывод - смотреть вручную
void testFourthTask(){
    size_t size = 4;
    domain array[4] = {{900, "google.mail.com"},
                       {50, "yahoo.com"},
                       {1, "intel.mail.com"},
                       {5, "wiki.org"}};
    fourthTaskAlgorithm(array, size);
}


void testFifthTask(){
    size_t rows1 = 3;
    size_t cols1 = 3;

    matrix m1 = createMatrixFromArray(
            (int[]) {
                1, 0, 1,
                1, 1, 0,
                1, 1, 0
            }, 3, 3
    );

    size_t result1 = 0;

    fifthTaskAlgorithm(m1, rows1, cols1, &result1);

    assert(result1 == 13);


    size_t rows2 = 3;
    size_t cols2 = 4;

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0, 1, 1, 0,
                    0, 1, 1, 1,
                    1, 1, 1, 0
            }, 3, 4
    );

    size_t result2 = 0;

    fifthTaskAlgorithm(m2, rows2, cols2, &result2);

    assert(result2 == 24);
}


void testSixthTask(){
    char s1[10] = "IIIDIDDD";
    size_t length1 = 8;
    char got1[10];
    size_t resLength1;
    sixthTaskAlgorithm(s1, length1, got1, &resLength1);
    char expected1[10] = "123549876";
    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "DDD";
    size_t length2 = 3;
    char got2[5];
    size_t resLength2;
    sixthTaskAlgorithm(s2, length2, got2, &resLength2);
    char expected2[10] = "4321";
    assert(strcmp(got2, expected2) == 0);
}

// не писал автотесты под вывод - смотреть вручную
void testSeventhTask(){
    int array1[6] = {3, 2, 1, 6, 0, 5};
    int lengthArray1 = 6;
    seventhTaskAlgorithm(array1, lengthArray1);

    int array2[3] = {3, 2, 1};
    int lengthArray2 = 3;
    seventhTaskAlgorithm(array2, lengthArray2);
}


void testEighthTask(){
    char s1[4] = "abc";
    size_t lengthS1 = 3;
    size_t indexes1[3] = {0, 1, 2};
    char got1[4];
    eighthTaskAlgorithm(s1, lengthS1, indexes1, got1);
    char expected1[4] = "abc";
    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "abap";
    size_t lengthS2 = 4;
    size_t indexes2[4] = {0, 3, 2, 1};
    char got2[5];
    eighthTaskAlgorithm(s2, lengthS2, indexes2, got2);
    char expected2[5] = "apab";
    assert(strcmp(got2, expected2) == 0);
}


void testNinthTask(){
    int numsArray[5] = {2, 4, 1, 3, 5};
    size_t lengthArray = 5;
    int controlNum = 3;
    char *firstFileName = "../firstFile.txt";
    char *secondFileName = "../secondFile.txt";
    vector v = createVector(10);
    ninthTaskAlgorithm(numsArray, lengthArray, controlNum,
                       firstFileName, secondFileName, &v);

    size_t expectedLength = 2;
    int expectedArrayNums[2] = {2, 1};

    assert(expectedLength == v.size);
    for (size_t ind = 0; ind < expectedLength; ind++){
        assert(v.data[ind] == expectedArrayNums[ind]);
    }
}


void testTenthTask(){
    char *fileName = "../tenthTask.txt";
    size_t countOutputLines = 3;
    char text[200] = "123\n456\n789\n0";
    tenthTaskAlgorithm(fileName, countOutputLines, text);
}

void testEleventhTask() {
    char dictionary1[5][25] = {"apple", "banana", "cherry", "orange", "pear"};
    char prefix1[25] = "b";
    int n = 5, q = 1;

    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%s\n", dictionary1[i]);
    }

    printf("%d %s\n", 1, prefix1);

    char dictionary2[5][25] = {"apple", "banana", "cherry", "orange", "pear"};
    char prefix2[25] = "ap";
    n = 5;
    q = 1;

    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%s\n", dictionary2[i]);
    }

    printf("%d %s\n", 3, prefix2);
}