#ifndef LAB_17_STRING_PROCESSING_H
#define LAB_17_STRING_PROCESSING_H

#include "string_.h"
#include <ctype.h>

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;


typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


int strcmpN(char *a, char *b, size_t size);

int getWord(char *beginSearch, WordDescriptor *word);

bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

char *getEndOfString(char *s);

void removeNonLetters(char *s);

void removeExtraSpaces(char *s);

void sortDigitsToEndWithOriginalOrder(char *s);

void replaceDigitsBySpaces(char *source, char *dest);

void replace(char *source, char *w1, char *w2);

bool isWordsStandWithOrder(char *s);

void getBagOfWords(BagOfWords *bag, char *s);

void outputBagReverse(BagOfWords *bag);

int countPalindromicWords(char *s);

void createNewFlipFlopStr(char *s1, char *s2, char *new);

void reverseWordOrder(char *s);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, WordDescriptor *w);

void getLastWordFromFirstThatInSecond(char *s1, char *s2, WordDescriptor *word);

void wordDescriptorToString(WordDescriptor word, char *destination);

int areWordsEqual(WordDescriptor w1, WordDescriptor w2);

bool hasStringSameWords(char *s);

bool hasTwoSameSymbolsWords(char *s1);

void sortWordsLetters(WordDescriptor *word);

void deleteAllLikeEndWords(char *s);

void findWordBeforeFirstBothInclusion(char *s1, char *s2, WordDescriptor *word);

void deleteWordsWithRepeatSymbols(char *s);

bool isWithoutRepeatSymbols(WordDescriptor *word);

void completeSmallestString(char *s1, char *s2);

bool allLettersWordInStr(WordDescriptor word, char *s);


#endif //LAB_17_STRING_PROCESSING_H
