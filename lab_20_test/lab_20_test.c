#include "lab_20_test.h"


void lab20Task1_test() {

    matrix m1 = createEmptySquareMatrix(3);

    int change1[4] = {1, 1, 2, 2};
    int change2[4] = {0, 0, 1, 1};
    int *changes[] = {change1, change2};

    task1(&m1, 2, changes);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    1, 2, 1,
                    0, 1, 1
            }, 3, 3
    );

    assert(areTwoMatricesEqual(&m1, &m2));
}


void lab20Task2_test() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    0, 1, 0,
                    1, 1, 1,
                    1, 0, 1,
                    1, 1, 0
            }, 4, 3
    );

    task2(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 1, 1,
                    1, 0, 1,
                    0, 0, 1,
                    1, 1, 0
            }, 4, 3
    );
    assert(areTwoMatricesEqual(&m1, &m2));
}


void lab20Task3_test() {
    int n = 3;

    matrix m1 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 35, 45,
                    15, 25, 35
            }, 3, 3
    );
    task3(&m1, n);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 25, 45,
                    15, 25, 35
            }, 3, 3
    );

    assert(areTwoMatricesEqual(&m1, &m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);

    n = 5;

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 40, 50,
                    15, 15, 10, 55, 15,
                    20, 25, 30, 35, 40,
                    5, 10, 20, 25, 35,
                    15, 20, 25, 30, 35,
            }, 5, 5
    );
    task3(&m3, n);

    matrix m4 = createMatrixFromArray(
            (int[]) {
                    10, 20, 30, 40, 50,
                    15, 15, 10, 55, 15,
                    20, 25, 25, 35, 40,
                    5, 10, 20, 25, 35,
                    15, 20, 25, 30, 35,
            }, 5, 5
    );

    assert(areTwoMatricesEqual(&m3, &m4));

    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
}


void lab20Task5_test() {

    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    1, 1, 0,
                    1, 1, 0
            }, 3, 3
    );

    int result1 = task5(&m1);

    assert(result1 == 13);

    freeMemMatrix(&m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1, 0,
                    1, 1, 0, 1,
                    0, 1, 0, 1
            }, 3, 4
    );

    int result2 = task5(&m2);

    assert(result2 == 11);

    freeMemMatrix(&m2);
}

void lab20Task6_test() {
    char pattern1[] = "IIIDIDDD";
    size_t n;
    char res[10];
    task6(pattern1, 8, res, &n);
    char res1[10] = "123549876";
    assert(strcmp(res, res1) == 0);

    char pattern2[] = "DDD";
    task6(pattern2, 3, res, &n);
    char res2[10] = "4321";
    assert(strcmp(res, res2) == 0);
}

void lab20Task8_test() {
    char *s = "abc";
    int indArr1[3] = {0, 1, 2};
    char res[3];
    task8(s, 3, indArr1, res);
    char exp[3] = "abc";
    assert(strcmp(res, exp) == 0);

    s = "abap";
    int indArr2[4] = {0, 3, 2, 1};
    char res2[4];
    task8(s, 3, indArr2, res2);
    char exp2[4] = "apab";
    assert(strcmp(res2, exp2) == 0);
}

void lab20Task9_test() {
    int a[5] = {2, 4, 1, 3, 5};
    int n = 5;
    int limiter = 3;
    vector v = createVector(10);
    task9(a, n, limiter, "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_9.1_20.txt",
          "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_9.1_20.txt", &v);

    int n2 = 2;
    int a2[2] = {2, 1};

    assert(n2 == v.size);
    for (int i = 0; i < n2; i++) {
        assert(v.data[i] == a2[i]);
    }
}