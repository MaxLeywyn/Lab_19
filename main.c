#include <windows.h>
#include "lab_20/lab_20.h"




int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n = 3;

    int q[2][4] = {{1,1,2,2},{0,0,1,1}};

    matrix m = createEmptySquareMatrix(n);

    task1(&m,2,q);

    outputMatrix(m);

    freeMemMatrix(&m);

    return 0;
}

