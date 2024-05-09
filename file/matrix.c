#include "matrix.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>


void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    if (*values == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    for (int i = 0; i < nRows; i++) {
        values[i] = (int *) malloc(sizeof(int) * nCols);
        if (values[i] == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }
    return (matrix) {values, nRows, nCols};
}


matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    if (ms == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}


void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; ++i) {
        m->values[i] = NULL;
        free(m->values[i]);
    }
    m->values = NULL;
    free(m->values);

    m->nRows = 0;
    m->nCols = 0;
}


void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; ++i) {
        freeMemMatrix(&ms[i]);
        printf("\n");
    }
    ms->values = NULL;
    free(ms->values);
}


void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; ++i) {
        for (int j = 0; j < m->nCols; ++j) {
            scanf("%d", &m->values[i][j]);
        }

    }
}


void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(&ms[i]);
    }
}


void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}


void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}


void swapRows(matrix *m, int i1, int i2) {
    assert(i1 < m->nRows && i2 < m->nRows);
    swap(&m->values[i1], &m->values[i2]);
}


void swapColumns(matrix *m, int j1, int j2) {
    for (int i = 0; i < m->nRows; ++i) {
        swap(&m->values[i][j1], &m->values[i][j2]);
    }
}


int getSum(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {

        sum += a[i];
    }
    return sum;
}


void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    int a[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        a[i] = criteria(m.values[i], m.nCols);
    }
    for (int i = 0; i < m.nRows; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
        swapRows(&m, j, i);
    }
}


void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    for (int i = 0; i < m.nCols; i++) {
        for (int j = i + 1; j < m.nCols; j++) {
            int *col_1 = (int *) malloc(m.nRows * sizeof(int));
            int *col_2 = (int *) malloc(m.nRows * sizeof(int));

            for (int k = 0; k < m.nRows; k++) {
                col_1[k] = m.values[k][i];
                col_2[k] = m.values[k][j];
            }

            if (criteria(col_1, m.nRows) > criteria(col_2, m.nRows)) {
                for (int k = 0; k < m.nRows; k++) {
                    int t = m.values[k][i];
                    m.values[k][i] = m.values[k][j];
                    m.values[k][j] = t;
                }
            }

            free(col_1);
            free(col_2);
        }
    }
}


bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}


bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }
    for (int i = 0; i < m1->nRows; ++i) {
        if (memcmp(m1->values[i], m2->values[i], m1->nCols * sizeof(int))!=0) {
            return false;
        }
    }
    return true;
}


bool isEMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (j == i && m->values[i][j] != 1) {
                return false;
            } else if (j != i && m->values[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}


bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }

    return true;
}


void transposeSquareMatrix(matrix *m) {
    assert(m->nRows == m->nCols);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int t = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = t;
        }
    }
}


position getMinValuePos(matrix m) {
    position min_element_position;
    int min_element = INT_MAX;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min_element) {
                min_element = m.values[i][j];
                min_element_position.rowIndex = i;
                min_element_position.colIndex = j;
            }
        }
    }
    return min_element_position;
}


position getMaxValuePos(matrix m) {
    position max_element_position;
    int max_element = INT_MIN;

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max_element) {
                max_element = m.values[i][j];
                max_element_position.rowIndex = i;
                max_element_position.colIndex = j;
            }
        }
    }
    return max_element_position;
}


matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}


matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices, int nRows, int nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

