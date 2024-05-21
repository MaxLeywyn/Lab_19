#include <windows.h>
#include "lab_20/lab_20.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

    matrix m = createMatrixFromArray((int[]) {
            1, 0, 1,
            1, 1, 0,
            1, 1, 0,
    }, 3, 3);


    printf(" %d", task5(&m));

    freeMemMatrix(&m);

    return 0;
}

