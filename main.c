#include <windows.h>
#include "lab_20/lab_20.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

    matrix m = createMatrixFromArray((int[]) {
            2, 1, 6, 9, 16,
            6, 9, 2, 16, 25,
            1, 7, 15, 40, 19,
            12, 9, 30, 3, 1,
            12, 20, 4, 11, 13,
    }, 5, 5);

    filterFunc(&m, 5);

    outputMatrix(m);

    freeMemMatrix(&m);

    return 0;
}

