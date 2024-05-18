#include "file_tests.h"

void task1_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_1.1.txt";
    int nMatrices = 5;
    matrix *ms = createArrayOfMatrixFromArray(
            (int[]) {
                    7, 5,
                    2, 1,

                    1, 5,
                    6, 3,

                    8, 3,
                    12, 3,

                    1, 3,
                    7, 9,

                    0, 0,
                    0, 0
            }, nMatrices, 2, 2
    );

    writeArrayInMatrix(fileName, ms, nMatrices);

    int readMatricesQuantity;
    matrix *result = readMatrixFromFile(fileName, &readMatricesQuantity);

    assert(nMatrices == readMatricesQuantity);

    matrix *expected = createArrayOfMatrixFromArray(
            (int[]) {
                    7, 5,
                    2, 1,

                    1, 5,
                    6, 3,

                    8, 3,
                    12, 3,

                    1, 7,
                    3, 9,

                    0, 0,
                    0, 0
            }, nMatrices, 2, 2
    );

    for (int i = 0; i < readMatricesQuantity; i++) {
        assert(areTwoMatricesEqual(&result[i], &expected[i]));
    }
    freeMemMatrices(ms, 5);
    freeMemMatrices(expected, 5);


    char *fileName2 = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_1.2.txt";
    nMatrices = 0;
    matrix *ms2 = createArrayOfMatrixFromArray(
            (int[]) {}, nMatrices, 0, 0
    );

    writeArrayInMatrix(fileName2, ms2, nMatrices);

    matrix *result2 = readMatrixFromFile(fileName2, &readMatricesQuantity);

    assert(nMatrices == readMatricesQuantity);

    matrix *expected2 = createArrayOfMatrixFromArray(
            (int[]) {}, nMatrices, 0, 0
    );

    for (int i = 0; i < readMatricesQuantity; i++) {
        assert(areTwoMatricesEqual(&result2[i], &expected2[i]));
    }
}

bool comp(double firstNum, double secondNum) {
    return (fabs(firstNum - secondNum) < 0.01);
}

void task2_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_2.1.txt";
    double numsArr[17] = {1, 2, 3, 4, 5, 6, 7,
                          8, 9, 10.111, 11.121212, 12,
                          13, 14, 15.158, 16, 17};
    size_t size = 17;

    writeNumsInFile(fileName, numsArr, size);

    double exception[17] = {1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00,
                            8.00, 9.00, 10.11, 11.12, 12.00,
                            13.00, 14.00, 15.16, 16.00, 17.00};

    double readNumsArr[17];

    readNumsFromFile("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_2.1.txt", readNumsArr, &size);

    for (int i = 0; i < size; i++) {
        assert(comp(readNumsArr[i], exception[i]));
    }


    char *fileName2 = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_2.2.txt";
    double numsArr2[0];
    size = 0;

    writeNumsInFile(fileName2, numsArr2, size);
    double exception2[0];

    double readNumsArr2[1];

    readNumsFromFile("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_2.2.txt", readNumsArr2, &size);

    for (int i = 0; i < size; i++) {
        assert(comp(readNumsArr2[i], exception2[i]));
    }
}

void task3_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_3.1.txt";
    char s[20];
    writeAnswerOfArithmeticExpressionToEnd(fileName);
    FILE *f = openFile(fileName, "r");

    fread(s, sizeof(char) * 15, 1, f);
    char *expected = "7 - 6 * 0 =7";
    assert(strcmp(expected, s) == 0);
    fclose(f);
}

void task4_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_4.1.txt";
    char fileName2[50] = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_4.2.txt";

    char s[200] = "valkyria chronicles persona yakuza burnout";
    char word[1] = "o";
    FILE *f1 = openFile(fileName, "w");
    fwrite(s, sizeof(char) * 42, 1, f1);
    fclose(f1);

    leftOnlyInclusionWords(word, fileName, fileName2);
    FILE *f2 = openFile(fileName, "r");
    char got[27];
    fread(got, sizeof(char) * 26, 1, f2);
    fclose(f2);

    char expected[27] = "chronicles persona burnout";
    assert(strcmp(got, expected) == 0);
}

void task5_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_5.1.txt";
    char fileName2[50] = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_5.2.txt";

    char s[200] = "valkyria chronicles persona yakuza burnout";
    FILE *f1 = openFile(fileName, "w");
    fwrite(s, sizeof(char) * 42, 1, f1);
    fclose(f1);

    leftOnlyLongestWord(fileName, fileName2);
    FILE *f2 = openFile(fileName, "r");
    char got[10];
    fread(got, sizeof(char) * 10, 1, f2);
    fclose(f2);

    char expected[10] = "chronicles";
    assert(strcmp(got, expected) == 0);
}

void task6_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_6.1.txt";
    double coefficients[] = {10.0, -7.0, 3.0, 1.0, -2.0, 1.0};
    int powers[] = {3, 2, 0, 2, 1, 0};
    int monQuantity[] = {3, 3};
    int polQuantity = 2;
    int x = 1;

    int got;
    leftPolynomsWhitNoXRoot(fileName, powers, coefficients, monQuantity, polQuantity, x, &got);
    int expected = 1;
    assert(got == expected);
}

void task7_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_7.1.txt";
    int numsArr[10] = {1, -2, -3, -4, -5, 6, 7, 10, 9, 8};
    size_t sizeArray = 10;

    vector positive = createVector(1);
    vector negative = createVector(1);

    writePosFirstNegSec(fileName, numsArr, sizeArray, &positive, &negative);

    int expectedPositive[6] = {1, 6, 7, 10, 9, 8};
    int expectedNegative[4] = {-2, -3, -4, -5};

    assert(positive.size == 6);
    assert(negative.size == 4);

    for (int i = 0; i < positive.size; i++) {
        assert(positive.data[i] == expectedPositive[i]);
    }

    for (int i = 0; i < negative.size; i++) {
        assert(negative.data[i] == expectedNegative[i]);
    }
}


void task8_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_8.1.txt";

    int nMatrices = 4;
    int matricesOrder = 3;
    matrix *ms = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 4, 0,
                    4, 2, 5,
                    0, 5, 3,

                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,

                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,

                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0
            }, nMatrices, matricesOrder, matricesOrder
    );

    changeNotSymmetricMatrixByTransposed(fileName, ms, nMatrices);

    matrix *expected = createArrayOfMatrixFromArray(
            (int[]) {
                    1, 4, 0,
                    4, 2, 5,
                    0, 5, 3,

                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,

                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,

                    0, 0, 0,
                    0, 0, 0,
                    0, 0, 0
            }, nMatrices, matricesOrder, matricesOrder
    );

    matrix *got = readMatrixFromBinFile(fileName);

    for (size_t i = 0; i < nMatrices; i++) {
        assert(areTwoMatricesEqual(&got[i], &expected[i]));
    }
}

void task9_test() {
    char *fileName = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_9.1.txt";
    int sportsmansQuantity = 4;
    sportsman sportsmansArr[sportsmansQuantity];

    sportsmansArr[0].name = "Leywyn Arthur Elvinov";
    sportsmansArr[0].bestResult = 100;

    sportsmansArr[1].name = "Bright Estel Eric";
    sportsmansArr[1].bestResult = 150;

    sportsmansArr[2].name = "Kruger Chad Nickolaev";
    sportsmansArr[2].bestResult = 250;

    sportsmansArr[3].name = "Nameless King Artorias";
    sportsmansArr[3].bestResult = 400;

    int sportsmansNeed = 2;
    sportsman readArraySportsmans[4];
    sportsman *rightSportsmans;

    formTeamOfBestSportsmans(fileName, sportsmansArr, sportsmansQuantity, sportsmansNeed,
                             readArraySportsmans, &rightSportsmans);

    int expected[2] = {250, 400};
    for (size_t i = 0; i < sportsmansNeed; i++) {
        assert(rightSportsmans[i].bestResult == expected[i]);
    }
}


void task10_test() {
    char *fileNameProducts = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_10.1.txt";
    char *fileNameOrders = "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_10.2.txt";

    size_t productsQuantity = 3;
    product productsArr[productsQuantity];

    productsArr[0].name = "Posion";
    productsArr[0].quantity = 5;
    productsArr[0].unitPrice = 100;
    productsArr[0].fullPrice = 500;

    productsArr[1].name = "Ethier";
    productsArr[1].quantity = 3;
    productsArr[1].unitPrice = 500;
    productsArr[1].fullPrice = 1500;

    productsArr[2].name = "Phoenix feather";
    productsArr[2].quantity = 1;
    productsArr[2].unitPrice = 1000;
    productsArr[2].fullPrice = 1000;

    size_t ordersQuantity = 3;
    order ordersArr[ordersQuantity];

    ordersArr[0].name = "Posion";
    ordersArr[0].quantity = 5;

    ordersArr[1].name = "Phoenix feather";
    ordersArr[1].quantity = 0;

    ordersArr[2].name = "Ethier";
    ordersArr[2].quantity = 2;

    product *readProductsArr;

    saveOnlyAvailableProductsByOrders(fileNameProducts, fileNameOrders, productsArr, productsQuantity,
                                      ordersArr, ordersQuantity, &readProductsArr);

    int expectedQuantity[3] = {0, 1, 1};
    int expectedFullPrice[3] = {0, 500, 1000};

    for (size_t i = 0; i < productsQuantity; i++) {
        assert(readProductsArr[i].quantity == expectedQuantity[i]);
        assert(readProductsArr[i].fullPrice == expectedFullPrice[i]);
    }
}
