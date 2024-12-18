#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <config.h>

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

typedef struct {
    WordCount hashTable[HASH_SIZE];
} HashMap;

void initHashMap(HashMap *map);

void addWord(HashMap *map, const char *word);

void printHashMap(HashMap *map);

int findWord(HashMap *map, const char *word);

#endif
