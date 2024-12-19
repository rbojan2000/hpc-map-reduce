#include <serial.h>

void serial_word_count(char *text, HashMap *word_count) {
    init_hash_map(word_count);

    int token_count;
    char **tokens = tokenize(text, &token_count);

    #if ENABLE_DEBUG
    printf("Number of tokens: %d\n", token_count);
    #endif

    for (int i = 0; i < token_count; i++) {
        add_word(word_count, tokens[i]);
    }

    free_tokens(tokens, token_count);
}
