#include <windows.h>
#include "lab_20/lab_20.h"




int main() {

    SetConsoleOutputCP(CP_UTF8);

    matrix m = createMatrixFromArray((int[]){
        0, 1, 1,
        1,1,1,
        1,1,0,
        0,0,1,
        },4,3);

    task2(&m);

    outputMatrix(m);

    freeMemMatrix(&m);

    return 0;
}

