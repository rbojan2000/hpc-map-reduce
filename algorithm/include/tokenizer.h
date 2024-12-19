#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char** tokenize(const char *text, int *word_count);
void free_tokens(char **tokens, int word_count);

#endif
