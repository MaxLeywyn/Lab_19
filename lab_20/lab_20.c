#include "lab_20.h"
#include <signal.h>
#include <unistd.h>
#include <conio.h>


#define N 300000
#define Q 5
#define LEN 1000000


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
    if (i_r2 != m.nRows - 1) i_r2++;

    if (i_c1 != 0) i_c1--;
    if (i_c2 != m.nCols - 1) i_c2++;

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
    int tempArr[m->nRows * m->nCols];
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            int c = countNear1(*m, i, j);
            if ((c < 2 || c > 3) && m->values[i][j] == 1) {
                tempArr[counter] = 0;
            } else if (c == 3 && m->values[i][j] == 0) {
                tempArr[counter] = 1;
            } else {
                tempArr[counter] = m->values[i][j];
            }
            counter++;
        }
    }
    counter = 0;
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            m->values[i][j] = tempArr[counter];
            counter++;
        }
    }
}


void readNearPixels(matrix m, size_t i_row, size_t i_col, int *a, int filterSize) {

    int c = filterSize / 2;

    size_t i_r1 = i_row - c;
    size_t i_r2 = i_row + c;
    size_t i_c1 = i_col - c;
    size_t i_c2 = i_col + c;

    int counter = 0;
    for (int i = i_r1; i <= i_r2; i++) {
        for (int j = i_c1; j <= i_c2; j++) {
            a[counter] = m.values[i][j];
            counter++;
        }
    }
}

int compare(const void *x1, const void *x2) {
    return (*(int *) x1 - *(int *) x2);
}

int countMiddle(int *a, size_t n) {
    qsort(a, n, sizeof(int), compare);
    return a[(n / 2) + 1];
}

void task3(matrix *m, int filterSize) {
    if (filterSize > m->nCols || filterSize > m->nRows) {
        printf("Filter size higher then matrix");
        return;
    }

    int c = filterSize / 2;

    for (int i_r1 = c; i_r1 <= m->nRows - c - 1; i_r1++) {
        for (int i_c1 = c; i_c1 <= m->nCols - c - 1; i_c1++) {
            size_t n = filterSize * filterSize;
            int a[n];
            readNearPixels(*m, i_r1, i_c1, a, filterSize);
            m->values[i_r1][i_c1] = countMiddle(a, n);
        }
    }
}


void task4(domen *arr, size_t size) {
    int closeInd[size];
    size_t closeCounter = 0;
    domen res[MAX_DOMENS_SIZE];
    size_t resSize = 0;

    for (int i = 0; i < size; i++) {
        res[resSize++] = arr[i];
    }

    while (closeCounter != size) {
        for (int i = 0; i < size; i++) {
            if (!searchNumInArray(closeInd, closeCounter, i)) {
                char *dotPtr = strchr(arr[i].nameOfSite, '.');
                if (dotPtr != NULL) {
                    dotPrtIsNotNull(arr, i, dotPtr, res, &resSize);
                } else {
                    closeInd[closeCounter++] = i;
                }
            }
        }
    }

    outputDomens(res, resSize);
}


int isSubMatrix1ByFilter(matrix *m, size_t i_row, size_t i_col, int *filterSize) {

    size_t i_r = i_row + (filterSize[0] - 1);
    size_t i_c = i_col + (filterSize[1] - 1);

    for (int i = i_row; i <= i_r; i++) {
        for (int j = i_col; j <= i_c; j++) {
            if (m->values[i][j] == 0) {
                return 0;
            }
        }
    }

    return 1;
}


int task5(matrix *m) {

    int counter = 0;
    int a[2] = {0, 0};
    for (int i = 1; i <= m->nRows; i++) {
        for (int j = 1; j <= m->nCols; j++) {
            int filterSizeI = m->nRows - i;
            int filterSizeJ = m->nCols - j;
            a[0] = i;
            a[1] = j;
            for (int i_r = 0; i_r <= filterSizeI; i_r++) {
                for (int i_c = 0; i_c <= filterSizeJ; i_c++) {
                    if (isSubMatrix1ByFilter(m, i_r, i_c, a)) {
                        counter++;
                    }
                }
            }
        }
    }
    return counter;
}


void task6(char *s, int size, char *res, size_t *resSize) {
    char buffer[10];
    int bufferSize = 0;
    int tempSize = 0;

    char num = '1';
    for (int i = 0; i < size; i++) {
        buffer[bufferSize++] = num++;
        if (s[i] == 'I') {
            while (bufferSize > 0)
                res[tempSize++] = buffer[--bufferSize];
        }
    }

    buffer[bufferSize++] = num;
    while (bufferSize > 0)
        res[tempSize++] = buffer[--bufferSize];

    res[tempSize] = '\0';
    *resSize = tempSize;
}


void task7(int *a, size_t size) {
    if (size == 0) {
        return;
    }

    int i = searchMaxNumIndex(a, 0, size - 1);
    knot *root = createKnot(a[i]);
    buildKnots(root, a, 0, i - 1, true);
    buildKnots(root, a, i + 1, size - 1, false);

    widthOfBypass(root);
    printf("\n");
}


void task8(char *s, size_t size, int *indArr, char *res) {
    for (int i = 0; i < size; i++) {
        res[i] = s[indArr[i]];
    }
    res[size] = '\0';
}


void printNumsToFile(int *a, size_t size, char *fileName) {
    FILE *file = openFile(fileName, "w");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", a[i]);
    }

    fclose(file);
}

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int limiter, char *wFileName) {
    FILE *rFile = openFile(rFileName, "r");
    FILE *wFile = openFile(wFileName, "w");

    int num;
    while (fscanf(rFile, "%d", &num) == 1) {
        if (num < limiter) {
            v->data[v->size++] = num;
            fprintf(wFile, "%d ", num);
        }
    }

    fclose(rFile);
    fclose(wFile);
}


void task9(int *a, size_t size, int limiter, char *readFileName, char *writeFileName, vector *v) {
    printNumsToFile(a, size, readFileName);
    readingNumsFilteringAndWriting(v, readFileName, limiter, writeFileName);
    shrinkToFit(v);
}


void printTextToFile(char *fileName, char *string) {
    FILE *file = openFile(fileName, "w");
    fprintf(file, "%s", string);
    fclose(file);
}


void signalHandler(int signum) {
    if (signum == SIGINT) {
        printf("\nCombination pressed.\n");
        exit(0);
    }
}


void task10(char *fileName, size_t strSize, char *text) {
    printTextToFile(fileName, text);

    FILE *file = openFile(fileName, "r");

    char strBuffer[STRING_BUFFER_SIZE];
    size_t count = 0;

    signal(SIGINT, signalHandler);

    while (fgets(strBuffer, STRING_BUFFER_SIZE, file) != NULL) {
        printf("%s", strBuffer);
        count++;

        if (count == strSize) {
            printf("Enter: Ctrl + C\n");

        }
    }
    fclose(file);
}


char strArr[N][Q];
int n, q;
char pi[LEN];

int binarySearchInWord(char *word) {
    int left = 0;
    int right = n - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (strncmp(strArr[middle], word, strlen(word)) < 0) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return right + 1;
}


void task11() {
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%s", strArr[i]);
    }

    for (int i = 0; i < q; i++) {
        int ki;
        scanf("%d %s", &ki, pi);
        int start = binarySearchInWord(pi);
        if (strncmp(strArr[start], pi, strlen(pi)) == 0 && (start + ki) < n) {
            printf("%d\n", start + ki);
        } else {
            printf("-1\n");
        }
    }
}
