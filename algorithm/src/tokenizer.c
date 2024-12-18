#include "tokenizer.h"

void removePunctuationAndNewlines(char *str) {
    char *read = str;
    char *write = str;

    while (*read) {
        if (!ispunct((unsigned char)*read) && *read != '\n') {
            *write++ = *read;
        } else if (isspace((unsigned char)*read)) {
            *write++ = ' ';
        }
        read++;
    }
    *write = '\0';
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

char** tokenize(const char *text, int *wordCount) {
    char *copy = strdup(text);
    
    removePunctuationAndNewlines(copy);

    char delimiter[] = " ";

    size_t capacity = 16;
    char **tokens = malloc(capacity * sizeof(char*));
    *wordCount = 0;

    char *token = strtok(copy, delimiter);
    while (token != NULL) {
        toLowerCase(token);

        if (*wordCount >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(char*));
        }
        tokens[*wordCount] = strdup(token);
        (*wordCount)++;
        token = strtok(NULL, delimiter);
    }

    free(copy);
    return tokens;
}

void freeTokens(char **tokens, int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
