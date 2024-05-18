#ifndef LAB_19_SPORTSMAN_H
#define LAB_19_SPORTSMAN_H



typedef struct sportsman{
    char *name;
    int bestResult;
} sportsman;

void writeSportsmansToBinFile(char *fileName, sportsman *sportsmanArr,
                              int sportsmanQuantity);

void quickSortSportsmans(sportsman *sportsmanArr, const int start, const int end);

sportsman* readSportsmansFromBinFile(char *fileName, int *sportsmanQuantity);

#endif //LAB_19_SPORTSMAN_H
