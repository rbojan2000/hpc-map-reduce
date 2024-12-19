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
    WordCount hash_table[HASH_SIZE];
} HashMap;

void init_hash_map(HashMap *map);

void add_word(HashMap *map, const char *word);

void print_hash_map(HashMap *map);

int find_word(HashMap *map, const char *word);

#endif
