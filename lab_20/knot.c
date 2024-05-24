#include "knot.h"


knot *createKnot(int k) {
    knot *newNode = (knot*) malloc(sizeof(knot));
    newNode->root = k;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


int searchMaxNumIndex(int *a, int start, int end) {
    int numTemp = a[start];
    int iTemp = start;

    for (int i = start + 1; i <= end; i++) {
        if (a[i] > numTemp) {
            numTemp = a[i];
            iTemp = i;
        }
    }

    return iTemp;
}


void buildKnots(knot *currentKnot, int *a, int start, int end, bool isLeft) {
    if (start > end) {
        return;
    }

    int i_max = searchMaxNumIndex(a, start, end);
    knot *newKnot = createKnot(a[i_max]);

    if (isLeft) {
        currentKnot->left = newKnot;
    } else {
        currentKnot->right = newKnot;
    }

    buildKnots(newKnot, a, start, i_max - 1, true);
    buildKnots(newKnot, a, i_max + 1, end, false);
}


void widthOfFirstBypass(knot *root) {
    if (root == NULL) {
        return;
    }

    knot *temp[100];
    int i_front = 0;
    int i_rear = 0;
    temp[i_rear++] = root;

    while (i_front < i_rear) {
        knot *current = temp[i_front++];
        printf("%d ", current->root);

        if (current->left != NULL) {
            temp[i_rear++] = current->left;
        }
        if (current->right != NULL) {
            temp[i_rear++] = current->right;
        }
    }
}