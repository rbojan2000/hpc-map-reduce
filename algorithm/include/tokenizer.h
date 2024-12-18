#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char** tokenize(const char *text, int *wordCount);
void freeTokens(char **tokens, int wordCount);

#endif
