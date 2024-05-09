#include <stdio.h>
#include <windows.h>
#include "file/file.h"



int main() {

    SetConsoleOutputCP(CP_UTF8);

    double res;

    calculateArithmeticExpression("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_3.1.txt",&res);

    FILE *f = openFile("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_3.1.txt","a");

    fprintf(f,"%d",res);

    fclose(f);

    return 0;
}
