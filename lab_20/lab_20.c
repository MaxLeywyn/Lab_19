#include "lab_20.h"


void incrementMatrixInArea(matrix *m, int *query) {
    for (int i = query[0]; i <= query[2]; i++) {
        for (int j = query[1]; j <= query[3]; j++) {
            m->values[i][j] += 1;
        }
    }
}

matrix createEmptySquareMatrix(int n){
    matrix m = getMemMatrix(n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            m.values[i][j]=0;
        }
    }
    return m;
}

//не забывать об очистке
void task1(matrix *m, int n, int query[n][4]){
    for (int i = 0; i < n; i++) {
        incrementMatrixInArea(m,query[i]);
    }
}