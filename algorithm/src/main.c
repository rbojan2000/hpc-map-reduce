#include <stdio.h>
#include <omp.h>
#include "hash_map.h"
#include "utils.h"
#include "tokenizer.h"

int main() {
    
    long file_size;
    char *text = readFile("../input-text/Anna-Karenina.txt", &file_size);
    
    if (!text) {
        return 1;
    }

    #if ENABLE_DEBUG
    printf("File content (%ld bytes):\n%s\n", file_size, text);
    #endif

    int wordCount;
    
    char **tokens = tokenize(text, &wordCount);

    printf("%d:\n", wordCount);
    for (int i = 0; i < wordCount; i++) {
        printf("Token: %s\n", tokens[i]);
    }

    freeTokens(tokens, wordCount);


    return 0;
}
