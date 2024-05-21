#include "domen.h"
#include "../file/file.h"

bool searchNumInArray(int *arr, size_t length, int num){
    for (size_t i = 0; i < length; i++){
        if (num == arr[i]){
            return true;
        }
    }

    return false;
}

size_t searchDomenInResults(domen *domens, size_t size, char *s){
    for (size_t i = 0; i < size; i++){
        if (strcmp(domens[i].nameOfSite, s) == 0){
            return i;
        }
    }

    return size;
}


void dotPrtIsNotNull(domen *arr, size_t i, char *dotPtr, domen *domens, size_t *sizeRes){
    strcpy(arr[i].nameOfSite, dotPtr + 1);
    size_t pos = searchDomenInResults(domens, *sizeRes,arr[i].nameOfSite);
    if (pos == *sizeRes){
        domens[*sizeRes] = arr[i];
        *sizeRes += 1;
    } else{
        domens[pos].visits += arr[i].visits;
    }
}


void outputDomens(domen *domens, size_t size){
    for (size_t i = 0; i < size; i++){
        printf("%ld %s\n", domens[i].visits, domens[i].nameOfSite);
    }
}