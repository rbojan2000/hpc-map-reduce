#include <hash_map.h>

void init_hash_map(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        map->hash_table[i].count = 0;
    }
}

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + tolower(*str++);
    return hash % HASH_SIZE;
}

void add_word(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    while (map->hash_table[index].count > 0 && strcmp(map->hash_table[index].word, word) != 0) {
        index = (index + 1) % HASH_SIZE;
    }
    if (map->hash_table[index].count == 0) {
        strncpy(map->hash_table[index].word, word, MAX_WORD_LEN);
    }
    map->hash_table[index].count++;
}

void print_hash_map(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (map->hash_table[i].count > 0) {
            printf("%s: %d\n", map->hash_table[i].word, map->hash_table[i].count);
        }
    }
}

int find_word(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    while (map->hash_table[index].count > 0) {
        if (strcmp(map->hash_table[index].word, word) == 0) {
            return map->hash_table[index].count;
        }
        index = (index + 1) % HASH_SIZE;
    }
    return 0;
}
