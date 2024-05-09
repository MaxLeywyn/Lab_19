#ifndef LAB_19_FILE_H
#define LAB_19_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "matrix.h"

FILE* openFile(char *fileName, char *action);

matrix *readMatrixFromFile(char *fileName, int *rCountMatrices);

void writeArrayInMatrix(char *fileName, matrix *ms, int nMatrices);

void writeNewNumInFile(char *readFileName,char *writeFileName);

void writeAnswerOfArithmeticExpressionToEnd(char *fileName);


#endif //LAB_19_FILE_H
