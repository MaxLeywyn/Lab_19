#include "lab_20.h"


void incrementMatrixInArea(matrix *m, int *query) {
    for (int i = query[0]; i <= query[2]; i++) {
        for (int j = query[1]; j <= query[3]; j++) {
            m->values[i][j] += 1;
        }
    }
}

matrix createEmptySquareMatrix(int n) {
    matrix m = getMemMatrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m.values[i][j] = 0;
        }
    }
    return m;
}

//не забывать об очистке
void task1(matrix *m, int n, int query[n][4]) {
    for (int i = 0; i < n; i++) {
        incrementMatrixInArea(m, query[i]);
    }
}


int countNear1(matrix m, size_t i_row, size_t i_col) {

    int count = 0;

    size_t i_r1 = i_row;
    size_t i_r2 = i_row;
    size_t i_c1 = i_col;
    size_t i_c2 = i_col;

    if (i_r1 != 0) i_r1--;
    if (i_r2 != m.nRows-1) i_r2++;

    if (i_c1 != 0) i_c1--;
    if (i_c2 != m.nCols-1) i_c2++;

    for (int i = i_r1; i <= i_r2; i++) {
        for (int j = i_c1; j <= i_c2; j++) {
            if (m.values[i][j] == 1) {
                if (!(j == i_col && i == i_row))
                    count++;
            }
        }
    }
    return count;
}

void task2(matrix *m) {
    int counter = 0;
    int tempArr[m->nRows*m->nCols];
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            int c = countNear1(*m, i, j);
            printf("%d\n", c);
            if ((c < 2 || c > 3) && m->values[i][j] == 1) {
                tempArr[counter] = 0;
            } else if (c == 3 && m->values[i][j] == 0) {
                tempArr[counter] = 1;
            } else {
                tempArr[counter]=m->values[i][j];
            }
            counter++;
        }
    }
    counter = 0;
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++){
            m->values[i][j]=tempArr[counter];
            counter++;
        }
    }
}