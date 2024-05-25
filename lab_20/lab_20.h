#ifndef LAB_19_LAB_20_H
#define LAB_19_LAB_20_H

#include "../file/matrix.h"
#include <stdlib.h>
#include "domen.h"
#include "knot.h"
#include "../file/file.h"
#include "signal.h"
#include <limits.h>
#include <conio.h>


#define MAX_DOMENS_SIZE 50
#define STRING_BUFFER_SIZE 100

matrix createEmptySquareMatrix(int n);

void task1(matrix *m, int n, int query[n][4]);

void task2(matrix *m);

void task3(matrix *m, int filterSize);

void task4(domen *arr, size_t size);

int task5(matrix *m);

void task6(char *s, int size, char *res, size_t *resSize);

void task7(int *a, size_t size);

void task8(char *s, size_t size, int *indArr, char *res);

void task9(int *a, size_t size, int limiter, char *readFileName, char *writeFileName, vector *v);

void task10(char *fileName, size_t strSize, char *text);



#endif //LAB_19_LAB_20_H
