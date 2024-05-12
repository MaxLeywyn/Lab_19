#include <stdio.h>
#include <windows.h>
#include "file/file.h"



int main() {

    SetConsoleOutputCP(CP_UTF8);

    leftOnlyInclusionWords("ea","F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_4.1.txt",
                            "F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_4.2.txt");

    return 0;
}

