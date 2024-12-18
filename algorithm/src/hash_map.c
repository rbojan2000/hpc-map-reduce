#include "hash_map.h"

void initHashMap(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        map->hashTable[i].count = 0;
    }
}

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + tolower(*str++);
    return hash % HASH_SIZE;
}

void addWord(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    while (map->hashTable[index].count > 0 && strcmp(map->hashTable[index].word, word) != 0) {
        index = (index + 1) % HASH_SIZE;
    }
    if (map->hashTable[index].count == 0) {
        strncpy(map->hashTable[index].word, word, MAX_WORD_LEN);
    }
    map->hashTable[index].count++;
}

void printHashMap(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (map->hashTable[i].count > 0) {
            printf("%s: %d\n", map->hashTable[i].word, map->hashTable[i].count);
        }
    }
}

int findWord(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    while (map->hashTable[index].count > 0) {
        if (strcmp(map->hashTable[index].word, word) == 0) {
            return map->hashTable[index].count;
        }
        index = (index + 1) % HASH_SIZE;
    }
    return 0;
}
