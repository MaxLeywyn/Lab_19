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

        for (int i_matrix = 0; i_matrix < nMatrices; i_matrix++) {
            for (int i = 0; i < dimensionMatrices; i++) {
                for (int j = 0; j < dimensionMatrices; j++) {
                    fscanf(file, "%d", &ms[i_matrix].values[i][j]);
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

        for (int i_matrix = 0; i_matrix < nMatrices; i_matrix++) {
            for (int i = 0; i < ms->nRows; i++) {
                for (int j = 0; j < ms->nCols; j++) {
                    fprintf(file, "%d ", ms[i_matrix].values[i][j]);
                }
                fprintf(file, "\n");
            }
        }
    }

    fclose(file);
}

void writeTransposedMatrices(char *rfileName, int *matrixCounter) {
    int counter;
    matrix *ms = readMatrixFromFile(rfileName, &counter);
    for (int i = 0; i < counter; i++) {
        transposeSquareMatrix(&ms[i]);
    }
    writeArrayInMatrix(rfileName, ms, counter);
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

bool wordIncludesSequence(WordDescriptor word, char *sequence,
                          size_t size) {
    size_t i_sequence = 0;
    while (word.begin != word.end && i_sequence < size) {
        if (*word.begin == sequence[i_sequence]) {
            i_sequence++;
        } else {
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
        if (wordIncludesSequence(bag.words[i], word, strlen(word))) {
            char a[20];
            wordDescriptorToString(bag.words[i], a);
            fprintf(file, "%s", a);
            fprintf(file, " ");
        }
    }
    fclose(file);
}

void getLongestWordsInLineFromFile(char *fileName, char *result) {
    FILE *file = openFile(fileName, "r");

    char *beginResult = result;
    char line[200];
    while (fgets(line, 200, file) != NULL) {
        char *begin = line;

        WordDescriptor lookingWord;
        size_t sizeLookingWord = 0;
        WordDescriptor word;
        while (getWord(begin, &word)) {
            size_t sizeWord = word.end - word.begin;
            if (sizeWord > sizeLookingWord) {
                sizeLookingWord = sizeWord;
                lookingWord = word;
            }
            begin = word.end;
        }
        if (sizeLookingWord > 0) {
            beginResult = copy(lookingWord.begin, lookingWord.end, beginResult);
            *beginResult = '\n';
            beginResult++;
        }
    }
    fclose(file);
}


void leftOnlyLongestWord(char *rFileName, char *wFileName) {
    char longestWord[200];
    getLongestWordsInLineFromFile(rFileName, longestWord);
    FILE *file = openFile(wFileName, "w");
    fprintf(file, "%s", longestWord);
    fclose(file);
}


void leftPolynomsWhitNoXRoot(char *fileName, int *powers, double *coefficients,
                             int *monQuantity, int polQuantity, int x, int *result) {
    writePolyToFile(fileName, powers, coefficients, monQuantity, polQuantity);

    Polynom *ps = readPolyFromFile(fileName);

    *result = sortedPoly(ps, x, polQuantity);

    savePolyResult(fileName, ps, polQuantity);
}

void writeNumsToBinFile(char *fileName, int *numsArr, size_t size) {
    FILE *file = openFile(fileName, "wb");
    fwrite(numsArr, sizeof(int), size, file);
    fclose(file);
}


void readFilterAndWriteNumsToBinFile(char *fileName,
                                  vector *positive,
                                  vector *negative) {
    FILE *file = openFile(fileName, "rb");

    size_t indPositive = 0;
    size_t indNegative = 0;

    int num;
    while (fread(&num, sizeof(int), 1, file) == 1) {
        if (num > 0) {
            pushBack(positive, num);
        } else {
            pushBack(negative, num);
        }
    }

    fclose(file);

    writeNumsToBinFile(fileName, positive->data, indPositive);
    writeNumsToBinFile(fileName, negative->data, indNegative);

    shrinkToFit(positive);
    shrinkToFit(negative);
}

void writePosFirstNegSec(char *fileName, int *numsArr, size_t size,
                         vector *positive, vector *negative) {
    writeNumsToBinFile(fileName, numsArr, size);

    readFilterAndWriteNumsToBinFile(fileName, positive, negative);
}


matrix *readMatrixFromBinFile(char *fileName) {
    FILE *file = openFile(fileName, "rb");
    int nMatrices;
    fread(&nMatrices, sizeof(int), 1, file);
    matrix *ms;

    if (nMatrices > 0) {
        int dimensionMatrices;
        fread(&dimensionMatrices, sizeof(int), 1, file);
        ms = getMemArrayOfMatrices(nMatrices,
                                   dimensionMatrices,
                                   dimensionMatrices);

        for (int i_matrix = 0; i_matrix < nMatrices; i_matrix++) {
            for (int j = 0; j < ms[i_matrix].nRows; j++) {
                fread(ms[i_matrix].values[j], sizeof(int),
                      ms[i_matrix].nCols, file);
            }
        }
    }

    fclose(file);
    return ms;
}

void wMatrixToBinFile(char *fileName, matrix *ms, int nMatrices) {
    FILE *file = openFile(fileName, "wb");

    fwrite(&nMatrices, sizeof(int), 1, file);
    if (nMatrices > 0) {
        fwrite(&ms[0].nRows, sizeof(int), 1, file);

        for (int i_matrix = 0; i_matrix < nMatrices; i_matrix++) {
            for (int j = 0; j < ms[i_matrix].nRows; j++) {
                fwrite(ms[i_matrix].values[j], sizeof(int),
                       ms[i_matrix].nCols, file);
            }
        }
    }

    fclose(file);
}


void changeNotSymmetricMatrixByTransposed(char *fileName, matrix *ms, int nMatrices) {
    wMatrixToBinFile(fileName, ms, nMatrices);

    matrix *msRes = readMatrixFromBinFile(fileName);
    for (size_t matrixInd = 0; matrixInd < nMatrices; matrixInd++) {
        if (!isSymmetricMatrix(&msRes[matrixInd])) {
            transposeSquareMatrix(&msRes[matrixInd]);
        }
    }

    wMatrixToBinFile(fileName, msRes, nMatrices);
}


void formTeamOfBestSportsmans(char *fileName, sportsman *sportsmanArr, int sportsmanQuantity,
               int sportsmanNeed, sportsman *readSportsmanArr,
               sportsman **rightSportsman) {

    if (sportsmanQuantity < sportsmanNeed) {
        printf("Число требуемых атлетов не покрыть имеющимся количеством");
        exit(1);
    }

    writeSportsmansToBinFile(fileName, sportsmanArr, sportsmanQuantity);

    int readSportsmanQuantity;
    readSportsmanArr = readSportsmansFromBinFile(fileName, &readSportsmanQuantity);
    quickSortSportsmans(readSportsmanArr, 0, readSportsmanQuantity - 1);

    int otherSportsmanQuantity = readSportsmanQuantity - sportsmanNeed;
    *rightSportsman = readSportsmanArr + otherSportsmanQuantity;

    writeSportsmansToBinFile(fileName, *rightSportsman, sportsmanNeed);
}


void saveOnlyAvailableProductsByOrders(char *fileNameProducts, char *fileNameOrders,
               product *productsArr, size_t productsQuantity,
               order *ordersArr, size_t ordersQuantity,
               product **readProductsIndicatorArr){
    writeProductsToBinFile(fileNameProducts, productsArr, productsQuantity);
    writeOrdersToBinFile(fileNameOrders, ordersArr, ordersQuantity);

    size_t readProductsQuantity;
    size_t notAvailableProductsQuantity = 0;
    product *readProductsArr = readProductsFromBinFile(fileNameProducts,
                                                   &readProductsQuantity);

    size_t readOrdersQuantity;
    order *readOrdersArr = readOrdersFromBinFile(fileNameOrders, &readOrdersQuantity);

    for (int i = 0; i < readOrdersQuantity; i++){
        size_t j = searchProductIndexInArray(
                readOrdersArr[i].name, readProductsArr,
                readProductsQuantity);

        readProductsArr[j].quantity -= readOrdersArr[i].quantity;
        readProductsArr[j].fullPrice -= readOrdersArr[i].quantity *
                                               readProductsArr[j].unitPrice;

        if (readProductsArr[j].quantity == 0){
            notAvailableProductsQuantity++;
        }
    }

    *readProductsIndicatorArr = readProductsArr;
    writeAvailableProductsInBinFile(fileNameProducts, readProductsArr, productsQuantity,
                              notAvailableProductsQuantity);
}