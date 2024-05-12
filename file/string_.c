//
// Created by Admin on 04.04.2024.
//
#include "string_.h"
#include <memory.h>
#include <ctype.h>

int strlen1(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

size_t strlen2(char *s) {
    int i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin) {
    char *end = begin;
    while (isspace(*end) && *end != '\0') {
        end++;
    }
    return end;
}

char *findSpace(char *begin) {
    char *end = begin;
    while (!isspace(*end) && *end != '\0') {
        end++;
    }
    return end;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !(isspace(*rbegin)))
        rbegin--;
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while ((*lhs != '\0' || *rhs != '\0') && *lhs == *rhs)
        lhs++, rhs++;
    return *lhs - *rhs;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination) {
    memcpy(beginDestination, beginSource, sizeof(char) * (endSource - beginSource));
    return beginDestination + sizeof(char) * (endSource - beginSource) + 1;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            memcpy(beginDestination, beginSource, sizeof(char));
            beginDestination++;
        }
        beginSource++;
    }
    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    while (rbeginSource != rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }
    return beginDestination;
}