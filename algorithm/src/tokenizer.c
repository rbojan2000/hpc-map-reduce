#include <tokenizer.h>

void remove_punctuation_and_new_lines(char *str) {
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

void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

char** tokenize(const char *text, int *token_count) {
    char *copy = strdup(text);
    
    remove_punctuation_and_new_lines(copy);

    char delimiter[] = " ";

    size_t capacity = 16;
    char **tokens = malloc(capacity * sizeof(char*));
    *token_count = 0;

    char *token = strtok(copy, delimiter);
    while (token != NULL) {
        to_lower_case(token);

        if (*token_count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(char*));
        }
        tokens[*token_count] = strdup(token);
        (*token_count)++;
        token = strtok(NULL, delimiter);
    }

    free(copy);
    return tokens;
}

void free_tokens(char **tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
