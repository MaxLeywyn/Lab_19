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
#include "sportsman.h"
#include "product.h"



FILE* openFile(char *fileName, char *action);

//1
void writeArrayInMatrix(char *fileName, matrix *ms, int nMatrices);

matrix *readMatrixFromFile(char *fileName, int *matrixCounter);
//2
void writeNumsInFile(char *fileName, double *a, size_t size);

        void readNumsFromFile(char *fileName, double *a, size_t *size);
//3
void writeAnswerOfArithmeticExpressionToEnd(char *fileName);
//4
void leftOnlyInclusionWords(char *word, char *rFileName, char *wFileName);
//5
void leftOnlyLongestWord(char *rFileName, char *wFileName);
//6
void leftPolynomsWhitNoXRoot(char *fileName, int *powers, double *coefficients,
                             int *monQuantity, int polQuantity, int x, int *result);
//7
void writePosFirstNegSec(char *fileName, int *numsArr, size_t size,
                         vector *positive, vector *negative);
//8
void changeNotSymmetricMatrixByTransposed(char *fileName, matrix *ms, int nMatrices);

matrix *readMatrixFromBinFile(char *fileName);
//9
void formTeamOfBestSportsmans(char *fileName, sportsman *sportsmanArr, int sportsmanQuantity,
                              int sportsmanNeed, sportsman *readSportsmanArr,
                              sportsman **rightSportsman);
//10
void saveOnlyAvailableProductsByOrders(char *fileNameProducts, char *fileNameOrders,
                                       product *productsArr, size_t productsQuantity,
                                       order *ordersArr, size_t ordersQuantity,
                                       product **readProductsIndicatorArr);



#endif //LAB_19_FILE_H
