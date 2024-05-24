#ifndef LAB_19_KNOT_H
#define LAB_19_KNOT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct knot {
    int root;
    struct knot *left;
    struct knot *right;
} knot;


knot *createKnot(int k);

int searchMaxNumIndex(int *a, int start, int end);

void buildKnots(knot *currentKnot, int *a, int start, int end, bool isLeft);

void widthOfFirstBypass(knot *root);

#endif //LAB_19_KNOT_H
