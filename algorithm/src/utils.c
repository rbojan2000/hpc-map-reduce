#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename, long *file_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *text = (char *)malloc((*file_size) + 1);
    if (!text) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    fread(text, 1, *file_size, file);
    text[*file_size] = '\0';
    fclose(file);

    return text;
}
