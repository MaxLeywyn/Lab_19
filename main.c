#include <windows.h>
#include "lab_20/lab_20.h"


int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n = 5;

    int a[] = {6, 8, 1 ,5, 6};

    vector v = createVector(n);

    task9(a,n,6,"F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_9_20.txt",
          "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_9.2_2.txt",&v);

    for (int i = 0; i < v.size; ++i) {
        printf("%d",v.data[i]);
    }

    deleteVector(&v);
}

