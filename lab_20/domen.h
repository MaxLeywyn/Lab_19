#ifndef LAB_19_DOMEN_H
#define LAB_19_DOMEN_H

#include "stdio.h"
#include "stdbool.h"

typedef struct domen{
    size_t visits;
    char nameOfSite[200];
} domen;

void dotPrtIsNotNull(domen *arr, size_t i, char *dotPtr,
                          domen *results, size_t *sizeRes);

bool searchNumInArray(int *array, size_t length, int num);

void outputResultDomains(domen *results, size_t size);

#endif //LAB_19_DOMEN_H
