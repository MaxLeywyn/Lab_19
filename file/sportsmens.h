#ifndef LAB_19_SPORTSMENS_H
#define LAB_19_SPORTSMENS_H

#include "file.h"

typedef struct sportsman{
    char *name;
    int bestResult;
} sportsman;

void writeSportsmansToBinFile(char *fileName, sportsman *sportsmanArr,
                              int sportsmanQuantity);

void quickSortSportsmans(sportsman *sportsmanArr, const int start, const int end);

sportsman* readSportsmansFromBinFile(char *fileName, int *sportsmanQuantity);

#endif //LAB_19_SPORTSMENS_H
