#include <windows.h>
#include "lab_20/lab_20.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1, 0,
                    1, 1, 0, 1,
                    0, 1, 0, 1
            }, 3, 4
    );

    printf("%d", task5(&m2));

    freeMemMatrix(&m2);

}

