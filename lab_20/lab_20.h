#ifndef LAB_19_LAB_20_H
#define LAB_19_LAB_20_H

#include "../file/matrix.h"
#include <stdlib.h>

matrix createEmptySquareMatrix(int n);

void task1(matrix *m, int n, int query[n][4]);

void task2(matrix *m);

void filterFunc(matrix *m, int filterSize);




#endif //LAB_19_LAB_20_H
