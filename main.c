#include <windows.h>
#include "lab_20/lab_20.h"

void testFourthTask(){
    size_t size = 4;
    domen arr[4] = {{900, "google.mail.com"},
                       {50, "yahoo.com"},
                       {1, "intel.mail.com"},
                       {5, "wiki.org"}};
    task4(arr, size);
}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    testFourthTask();

    return 0;
}

