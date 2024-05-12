#ifndef LAB_19_POLYNOM_H
#define LAB_19_POLYNOM_H

#include <malloc.h>
#include "file.h"


typedef struct Monomial{
    int power;
    double coefficients;
} Monomial;


typedef struct Polynom{
    int monomialQuantity;
    struct Monomial *data;
} Polynom;


Polynom createPolynomFromArray(int *powers, double *coefficients, int argsQuantity);

Polynom* createPolynomsFromArray(int *powers, double *coefficients,
                                 int *monQuantity, int polQuantity);

Polynom loadPolynomFromFile(FILE *f);

Polynom* loadPolynomsFromFile(FILE *f, int *polQuantity);

void savePolynomToFile(Polynom p, FILE *f);

void savePolynomsToFile(Polynom *ps, FILE *f, int polQuantity);

double calculatePolynomByX(Polynom p, double x);

void freePolynom(Polynom * p);

Polynom* readPolyFromFile(char *fileName);

void writePolyToFile(char *fileName, int *powers, double *coefficients,
                     int *monQuantity, int polQuantity);

int sortedPoly(Polynom* ps, int x, int polQuantity);

void savePolyResult(char *fileName, Polynom *ps, int polQuantity);

#endif //LAB_19_POLYNOM_H
