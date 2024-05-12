#ifndef LAB_19_FILE_H
#define LAB_19_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "matrix.h"
#include "string_processing.h"
#include "polynom.h"
#include "math.h"
#include "vector.h"


FILE* openFile(char *fileName, char *action);

//1
void writeArrayInMatrix(char *fileName, matrix *ms, int nMatrices);
//2
void writeNewNumInFile(char *readFileName,char *writeFileName);
//3
void writeAnswerOfArithmeticExpressionToEnd(char *fileName);
//4
void leftOnlyInclusionWords(char *word, char *rFileName, char *wFileName);
//5
void leftOnlyLongestWord(char *rFileName, char *wFileName);
//6
void leftPolynomsWithNoXRoot(char *rFileName, char *wFileName, double x);
//7
void writePosFirstNegSec(char *fileName, int *numsArr, size_t size,
                         vector *positive, vector *negative);
//8
void changeNotSymmetricMatrixByTransposed(char *fileName, matrix *ms, int nMatrices);
//9




#endif //LAB_19_FILE_H
