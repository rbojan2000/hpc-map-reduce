#include <stdio.h>
#include <omp.h>
#include "hash_map.h"

int main() {
    
    long file_size;
    char *text = readFile("../input-text/text.txt", &file_size);
    
    if (!text) {
        return 1;
    }

    #if ENABLE_DEBUG
    printf("File content (%ld bytes):\n%s\n", file_size, text);
    #endif

    free(text);

    HashMap map1;
    initHashMap(&map1);

    addWord(&map1, "apple");
    addWord(&map1, "banana");
    addWord(&map1, "apple");

    printHashMap(&map1);

    printf("apple found: %d\n", findWord(&map1, "apple"));
    return 0;
}
