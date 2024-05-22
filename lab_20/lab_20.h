#ifndef LAB_19_LAB_20_H
#define LAB_19_LAB_20_H

#include <stdlib.h>
#include "../file/matrix.h"
#include <stdlib.h>
#include "domen.h"

#define MAX_DOMENS_SIZE 50

matrix createEmptySquareMatrix(int n);

void task1(matrix *m, int n, int query[n][4]);

void task2(matrix *m);

void task3(matrix *m, int filterSize);

void task4(domen *arr, size_t size);

int task5(matrix *m);

void task6(char *s, int size, char *res, size_t *resSize);



void task8(char *s, size_t size, int *indArr, char *res);

#endif //LAB_19_LAB_20_H
