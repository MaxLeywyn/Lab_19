#include "string_processing.h"
#include <memory.h>
#include <stdlib.h>

BagOfWords _bag;

char _stringBuffer[MAX_STRING_SIZE + 1];


//2
char *getEndOfString(char *s) {
    while (*s != '\0')
        s++;
    return s;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

//2
void removeExtraSpaces(char *s) {
    size_t i = 0;
    size_t j = 0;
    size_t spaces = 0;

    for (i; *(s + i) != '\0'; i++) {
        if (*(s + i) != ' ') {
            *(s + (j++)) = *(s + i);
            spaces = 0;
        } else if (!spaces && j > 0) {
            *(s + (j++)) = ' ';
            spaces = 1;
        }
    }
    *(s + j) = '\0';
}

//3


int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}


void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend) + 1;

    if ((word->end - rend) < 0) {
        return 0;
    }
    word->begin = (findSpaceReverse(word->end, rend) + 1);

    return 1;
}


//Преобразовать строку таким образом, чтобы цифры каждого слова были
//перенесены в конец слова без изменения порядка следования их в слове, а
//буквы – в начало.


void digitToEndWithOriginalOrder(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIf(_stringBuffer,
                               endStringBuffer,
                               word.begin, isalpha);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isdigit);
}


void sortDigitsToEndWithOriginalOrder(char *s) {
    WordDescriptor word;
    while (*s != '\0') {
        if (getWord(s, &word) && (!isspace(*s))) {
            digitToEndWithOriginalOrder(word);
            printf("%d ", (word.end - word.begin));
            s += (word.end - word.begin);
        }
        if (isspace(*s))
            s++;
    }
}

//char a[13]="3ewe 5fed34 " - пример


//4
void replaceDigitsBySpaces(char *source, char *dest) {
    size_t i = 0;
    size_t j = 0;

    while (*source != '\0') {
        if (isdigit(*(source + i))) {
            int numSpaces = *(source + i) - '0';
            for (int k = 0; k < numSpaces && j < MAX_STRING_SIZE - 1; k++) {
                *(dest + (j++)) = ' ';
            }
        } else if (j < MAX_STRING_SIZE - 1) {
            *(dest + (j++)) = *(source + i);
        }
        i++;
    }
    *(dest + j) = '\0';
}

//5
int strcmpN(char *a, char *b, size_t size) {
    for (int i = 0; i < size; ++i) {
        if (*(a + i) != *(b + i)) {
            return 0;
        }
    }
    return 1;
}


void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    printf("%d %d ", w1Size, w2Size);
    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    size_t i = 0;
    size_t j = 0;
    for (i; i < strlen_(readPtr); i++) {
        if (*(readPtr + i) == *w1 && strcmpN((readPtr + i), w1, w1Size) == 1) {
            memcpy((recPtr + j), w2, w2Size);
            j += w2Size;
            i += w1Size - 1;
        } else {
            *(recPtr + (j++)) = *(readPtr + i);
        }
    }
    *(recPtr + j) = '\0';
}


//6
int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    size_t size_1 = w1.end - w1.begin;
    if (size_1 == (w2.end - w2.begin))
        return 0;
    size_t i = 0;
    while (*(w1.begin + i) == *(w2.begin + i) && i != size_1) {
        i++;
    }
    return *w1.begin - *w2.begin;//-x - earlier
}


bool isWordsStandWithOrder(char *s) {
    WordDescriptor word;// 1 -cur, 2 - next,
    char *end = getEndOfString(s);
    getWord(s, &word);
    s += (word.end - word.begin);

    while (s != end) {
        WordDescriptor word2;
        if (getWord(s, &word2) != 0 && areWordsEqual(word, word2) > 0) {
            return 0;
        } else if (areWordsEqual(word, word2) <= 0 && getWord(s, &word2) != 0) {
            word.begin = word2.begin;
            word.end = word2.end;
            s += (word.end - word.begin);
        } else
            s++;
    }
    return 1;
}


//7
void getBagOfWords(BagOfWords *bag, char *s) {
    char *end = getEndOfString(s);
    size_t counter = 0;
    while (getWord(s, &(bag->words[counter]))) {
        s += (bag->words[counter].end - bag->words[counter].begin) + 1;
        counter++;
    }
    bag->size = counter;
}

void outputBagReverse(BagOfWords *bag) {
    for (int i = 0; i < bag->size; ++i) {
        for (int j = 0; j < (bag->words[i].end - bag->words[i].begin); ++j) {
            printf("%c", *bag->words[i].begin + j);
        }
        printf("\n");
    }
}


//8
char *findLetter(char *begin) {
    char *end = begin;
    while ((*end < 'a' && *end > 'z') && *end != '\0') {
        end++;
    }
    return end;
}

char *findComma(char *begin) {
    char *end = begin;
    while (*end != ',' && *end != '\0') {
        end++;
    }
    return end;
}

int getWordWithComma(char *beginSearch, WordDescriptor *word) {
    word->begin = findLetter(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findComma(word->begin) - 1;
    return 1;
}


int countPalindromicWords(char *s) {
    int counter = 0;
    WordDescriptor word1;
    while (getWordWithComma(s, &word1)) {
        int i = 0, c = 0;
        int half_size = (word1.end - word1.begin + 1) / 2;
        printf("%s", word1.begin);
        printf("  %d  ", half_size);

        for (; i < half_size; i++) {
            if (*(word1.begin + i) == *(word1.end - i))
                c++;
            printf("  %d  ", c);
        }
        if (c == half_size) {
            counter++;
        }
        printf("  %d\n", counter);
        s += ((word1.end + 1) - (word1.begin - 1));
    }

    return counter;
}

//9
void createNewFlipFlopStr(char *s1, char *s2, char *new) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            copy(word1.begin, word1.end, new);
            beginSearch1 += (word1.end - word1.begin + 1);
            new += (word1.end - word1.begin);
            *new = ' ';
            new++;
        }
        if (isW2Found) {
            copy(word2.begin, word2.end, new);
            beginSearch2 += (word2.end - word2.begin + 1);
            new += (word2.end - word2.begin);
            *new = ' ';
            new++;
        }
    }
    *new = '\0';
}

//10
void reverseWordOrder(char *s) {
    char *begin = _stringBuffer;
    char *end = copy(s, getEndOfString(s), _stringBuffer);
    WordDescriptor word;
    while (getWordReverse(end, begin, &word)) {
        s = copy(word.begin, word.end, s);
        end = word.begin - 1;
        *s = ',';
        s++;
    }
    *s = '\0';
}


//11
bool searchAInWord(WordDescriptor word) {
    while (word.begin != word.end) {
        if (*word.begin == 'A' || *word.begin == 'a') {
            return true;
        }
        word.begin++;
    }
    return false;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    WordDescriptor word, wordPrev;
    bool isFirst = 1;
    while (getWord(s, &word)) {
        if (searchAInWord(word) && isFirst) {
            w->begin = word.begin;
            w->end = word.end;
            return FIRST_WORD_WITH_A;
        } else if (searchAInWord(word) && (!isFirst)) {
            w->begin = wordPrev.begin;
            w->end = wordPrev.end;
            return WORD_FOUND;
        } else if (!searchAInWord(word)) {
            isFirst = 0;
            wordPrev.begin = word.begin;
            wordPrev.end = word.end;
            s += (word.end - word.begin);
        }
    }
    if (isFirst) {
        return EMPTY_STRING;
    } else {
        return NOT_FOUND_A_WORD_WITH_A;
    }
}

//12
void wordDescriptorToString(WordDescriptor word, char *destination) {
    destination = copy(word.begin, word.end, destination);
    *destination = '\0';
}


void getLastWordFromFirstThatInSecond(char *s1, char *s2, WordDescriptor *word) {
    BagOfWords bag1, bag2;
    WordDescriptor wordLast;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);
    for (int i = 0; i < bag1.size; i++) {
        for (int j = 0; j < bag2.size; j++) {
            if (areWordsEqual(bag1.words[i], bag2.words[j])) {
                wordLast.begin = bag1.words[i].begin;
                wordLast.end = bag1.words[i].end;
            }
        }
    }
    word->begin = wordLast.begin;
    word->end = wordLast.end;
}


//13
bool hasStringSameWords(char *s) {
    BagOfWords bag1;
    getBagOfWords(&bag1, s);
    for (int i = 0; i < bag1.size; i++) {
        for (int j = 0; j < bag1.size; j++) {
            if (areWordsEqual(bag1.words[i], bag1.words[j]) && i != j) {
                return 1;
            }
        }
    }
    return 0;
}

//14
void sortWordsLetters(WordDescriptor *word) {
    int size = (word->end - word->begin);

    for (int i = 0; i < size; i++) {
        char *swap_pos = (word->begin + i);
        for (int j = i + 1; j < size; j++) {
            if (*(word->begin + i) > *(word->begin + j)) {
                swap_pos = (word->begin + j);
            }
        }
        char temp = *swap_pos;
        *swap_pos = *(word->begin + i);
        *(word->begin + i) = temp;
    }

}

bool hasTwoSameSymbolsWords(char *s1) {
    BagOfWords bag1, bag2;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s1);
    for (int i = 0; i < bag1.size; ++i) {
        sortWordsLetters(&bag1.words[i]);
    }
    for (int i = 0; i < bag2.size; ++i) {
        sortWordsLetters(&bag2.words[i]);
    }
    for (int i = 0; i < bag1.size; i++) {
        for (int j = 0; j < bag2.size; j++) {
            if (areWordsEqual(bag1.words[i], bag2.words[i]))
                return 1;
        }
    }
    return 0;
}


//15
void deleteAllLikeEndWords(char *s) {
    BagOfWords bag;
    getBagOfWords(&bag, s);
    for (int i = 0; i < bag.size - 1; i++) {
        if (!areWordsEqual(bag.words[i], bag.words[bag.size - 1])) {
            s = copy(bag.words[i].begin, bag.words[i].end, s);
            *s = ' ';
            s++;
        }
    }
    *s = '\0';
}

//16
void findWordBeforeFirstBothInclusion(char *s1, char *s2, WordDescriptor *word) {
    BagOfWords bag1, bag2;
    WordDescriptor resWord;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);
    bool isWordFound = false;
    while (!isWordFound) {
        for (int i = 0; i < bag1.size; i++) {
            for (int j = 0; j < bag2.size; j++) {
                if (areWordsEqual(bag1.words[i], bag2.words[j])) {
                    if (i == 0)
                        i++;
                    resWord.begin = bag1.words[i - 1].begin;
                    resWord.end = bag1.words[i - 1].end;
                    isWordFound = true;
                }
            }
        }
    }
    word->begin = resWord.begin;
    word->end = resWord.end;
}


//17
bool isWithoutRepeatSymbols(WordDescriptor *word) {
    sortWordsLetters(word);
    int size = (word->end - word->begin);
    for (int i = 0; i < size - 1; i++) {
        if (*(word->begin + i) == *(word->begin + i + 1)) {
            return 0;
        }
    }
    return 1;
}

void deleteWordsWithRepeatSymbols(char *s) {
    char *begin = s;
    char *b_buffer = _stringBuffer;
    char *e_buffer = copy(s, getEndOfString(s), _stringBuffer);
    BagOfWords bag_sort1, bag_sort2;
    getBagOfWords(&bag_sort1, b_buffer);
    getBagOfWords(&bag_sort2, begin);

    for (int i = 0; i < bag_sort1.size; i++) {
        if (isWithoutRepeatSymbols(&bag_sort2.words[i])) {
            begin = copy(bag_sort1.words[i].begin, bag_sort1.words[i].end, begin);
            *begin = ' ';
            begin++;
        }
    }
    *begin = '\0';
}


//18
void completeSmallestString(char *s1, char *s2) {
    BagOfWords bag1, bag2;
    char *end2 = getEndOfString(s2);
    char *end1 = getEndOfString(s1);
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);
    int var = 0;
    if (bag1.size > bag2.size) {
        var = 1;
        int diff = (bag1.size - bag2.size);
        for (int i = 0; i < diff; i++) {
            end2 = copy(bag1.words[bag2.size + i].begin, bag1.words[bag2.size + i].end, end2);
            *end2 = ' ';
            end2++;
        }
    } else if (bag1.size < bag2.size) {
        var = 2;
        int diff = (bag2.size - bag1.size);
        for (int i = 0; i < diff; i++) {
            end1 = copy(bag2.words[bag1.size + i].begin, bag2.words[bag1.size + i].end, end1);
            *end1 = ' ';
            end1++;
        }
    }
    if (var == 2)
        *end1 = '\0';
    else if (var == 1)
        *end2 = '\0';
}


//19
int compareChars(const void *x1, const void *x2) {
    return (*(char *) x1 - *(char *) x2);
}


bool allLettersWordInStr(WordDescriptor word, char *s) {
    if (*word.begin == '\0') {
        return true;
    }
    char *sEnd = getEndOfString(s);
    qsort(s, sEnd - s, sizeof(char), compareChars);
    qsort(word.begin, word.end - word.begin, sizeof(char), compareChars);
    while (word.begin != word.end && s != sEnd) {
        if (*word.begin < *s) {
            return false;
        } else if (*word.begin > *s) {
            s++;
        } else {
            word.begin++;
            s++;
        }
    }
    return word.begin == word.end;
}