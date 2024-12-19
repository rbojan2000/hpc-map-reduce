#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *read_file(const char *filename, long *file_size);
char *repeat_text(char *text, long file_size, int n);

#endif
