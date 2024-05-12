#include "sportsmens.h"

void swapSportsmans(sportsman *const firstNum, sportsman *const secondNum){
    sportsman temp = *firstNum;
    *firstNum = *secondNum;
    *secondNum = temp;
}

int partitionSportsmans(sportsman *sportsmanArr, const int start, const int end){
    int pivot = sportsmanArr[end].bestResult;
    int i_pivot = start;
    for (int i = start; i < end; i++){
        if (sportsmanArr[i].bestResult <= pivot){
            swapSportsmans(&sportsmanArr[i], &sportsmanArr[i_pivot]);
            i_pivot++;
        }
    }

    swapSportsmans(&sportsmanArr[i_pivot], &sportsmanArr[end]);
    return i_pivot;
}

void quickSortSportsmans(sportsman *sportsmanArr, const int start, const int end){
    if (start >= end){
        return;
    }
    int pivot = partitionSportsmans(sportsmanArr, start, end);
    quickSortSportsmans(sportsmanArr, start, pivot - 1);
    quickSortSportsmans(sportsmanArr, pivot + 1, end);
}

void writeSportsmansToBinFile(char *fileName, sportsman *sportsmanArr,
                        int sportsmanQuantity){
    FILE *file = openFile(fileName, "wb");
    fwrite(&sportsmanQuantity, sizeof(int), 1, file);

    for (size_t i = 0; i < sportsmanQuantity; i++){
        fwrite(&sportsmanArr[i], sizeof(sportsman), 1, file);
    }
    fclose(file);
}


sportsman readSportsmanDataFromBinFile(FILE *file){
    sportsman data;
    fread(&data, sizeof(sportsman), 1, file);
    return data;
}


sportsman* readSportsmansFromBinFile(char *fileName, int *sportsmanQuantity){
    FILE *file = openFile(fileName, "rb");
    fread(sportsmanQuantity, sizeof (int), 1, file);
    sportsman *buffer = malloc(*sportsmanQuantity * sizeof(sportsman));
    for (size_t i = 0; i < *sportsmanQuantity; i++){
        buffer[i] = readSportsmanDataFromBinFile(file);
    }
    fclose(file);
    return buffer;
}