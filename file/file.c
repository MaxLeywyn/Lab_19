#include "file.h"


FILE *openFile(char *fileName, char *action) {
    FILE *file = fopen(fileName, action);
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }
    return file;
}

matrix *readMatrixFromFile(char *fileName, int *matrixCounter) {
    FILE *file = openFile(fileName, "r");

    int nMatrices;
    matrix *ms;
    fscanf(file, "%d", &nMatrices);

    if (nMatrices > 0) {
        int dimensionMatrices;
        fscanf(file, "%d", &dimensionMatrices);

        ms = getMemArrayOfMatrices(nMatrices,
                                   dimensionMatrices,
                                   dimensionMatrices);

        for (int matrix_i = 0; matrix_i < nMatrices; matrix_i++) {
            for (int row_i = 0; row_i < dimensionMatrices; row_i++) {
                for (int col_i = 0; col_i < dimensionMatrices; col_i++) {
                    fscanf(file, "%d", &ms[matrix_i].values[row_i][col_i]);
                }
            }
        }
    }

    *matrixCounter = nMatrices;
    fclose(file);

    return ms;
}

void writeArrayInMatrix(char *fileName, matrix *ms, int nMatrices) {
    FILE *file = openFile(fileName, "w");

    fprintf(file, "%d\n", nMatrices);

    if (nMatrices > 0) {
        fprintf(file, "%d\n", ms->nRows);

        for (int indMatrix = 0; indMatrix < nMatrices; indMatrix++) {
            for (int indRow = 0; indRow < ms->nRows; indRow++) {
                for (int indCol = 0; indCol < ms->nCols; indCol++) {
                    fprintf(file, "%d ", ms[indMatrix].values[indRow][indCol]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}

void writeTransposedMatrices(char *fileName, int *matrixCounter) {
    int counter;
    matrix *ms = readMatrixFromFile("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_1.txt", &counter);
    for (int i = 0; i < counter; i++) {
        transposeSquareMatrix(&ms[i]);
    }
    writeArrayInMatrix("F:\\Git\\Lab_19\\cmake-build-debug\\data\\f_2.txt", ms, counter);
}


void readNumsFromFile(char *fileName, double *a, size_t *size) {
    FILE *file = openFile(fileName, "r+");
    size_t i = 0;
    while (fscanf(file, "%lf", &a[i]) == 1) {
        i++;
    }
    *size = i;
    fclose(file);
}


void writeNumsInFile(char *fileName, double *a, size_t size) {
    FILE *file = openFile(fileName, "w");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%.2f\n", a[i]);
    }
    fclose(file);
}

void writeNewNumInFile(char *readFileName, char *writeFileName) {
    size_t size = 200;
    double a[size];
    readNumsFromFile(readFileName, a, &size);
    writeNumsInFile(writeFileName, a, size);
}


double doOperation(double num1, double num2, char operation) {
    double result;
    if (operation == '/') {
        if (num2 == 0) {
            printf("Деление на 0");
            exit(1);
        }
        result = num1 / num2;
    } else if (operation == '*') {
        result = num1 * num2;
    } else if (operation == '-') {
        result = num1 - num2;
    } else {
        result = num1 + num2;
    }

    return result;
}


double calculate(double *numArr, char *operationsArr, size_t i_sign) {
    double result;

    if (i_sign == 1) {
        result = doOperation(numArr[0], numArr[1], operationsArr[0]);
    } else {
        if ((operationsArr[0] == '-' || operationsArr[0] == '+') &&
            (operationsArr[1] == '/' || operationsArr[1] == '*')) {
            result = doOperation(doOperation(numArr[1], numArr[2],
                                             operationsArr[1]), numArr[0], operationsArr[0]);
        } else {
            result = doOperation(doOperation(numArr[0], numArr[1],
                                             operationsArr[0]), numArr[2], operationsArr[1]);
        }
    }

    return result;
}


void calculateArithmeticExpression(char *fileName, double *result) {
    FILE *file = openFile(fileName, "r");

    double numArr[3];
    char operationsArr[3];
    size_t i_num = 0;
    size_t i_sign = 0;
    char c;
    while (fscanf(file, "%c", &c) == 1) {
        if (isdigit(c)) {
            numArr[i_num++] = c - '0';
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            operationsArr[i_sign++] = c;
        }
    }


    *result = calculate(numArr, operationsArr, i_sign);
    fclose(file);
}

void writeAnswerOfArithmeticExpressionToEnd(char *fileName) {
    double res;
    calculateArithmeticExpression(fileName, &res);
    FILE *f = openFile(fileName, "a");
    fprintf(f, "%lf", res);
    fclose(f);
}


char full_string[200];

void readWordsFromFile(char *fileName, BagOfWords *bag) {
    FILE *file = openFile(fileName, "r");
    char a[20];
    size_t j = 0;
    while (fscanf(file, "%s", a) == 1) {
        copy(a, (a + strlen(a)), full_string + j);
        j += strlen(a);
        *(full_string + j) = ' ';
        j++;
    }
    getBagOfWords(bag, full_string);
    fclose(file);
}

bool wordIncludesSequence(WordDescriptor word, char* sequence,
                          size_t size){
    size_t i_sequence = 0;
    while (word.begin != word.end && i_sequence < size){
        if (*word.begin == sequence[i_sequence]){
            i_sequence++;
        } else{
            i_sequence = 0;
        }
        word.begin++;
    }
    return i_sequence == size;
}

void leftOnlyInclusionWords(char *word, char *rFileName, char *wFileName) {
    BagOfWords bag;
    readWordsFromFile(rFileName, &bag);
    size_t sizeOfWord = strlen(word);
    FILE *file = openFile(wFileName, "a");
    for (int i = 0; i < bag.size; i++) {
        if(wordIncludesSequence(bag.words[i],word, strlen(word))){
            char a[20];
            wordDescriptorToString(bag.words[i],a);
            fprintf(file, "%s", a);
            fprintf(file, " ");
        }
    }
    fclose(file);
}








