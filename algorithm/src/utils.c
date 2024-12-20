#include <utils.h>

char *read_file(const char *filename, long *file_size) {
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

char *repeat_text(char *text, long file_size, int n) {
    char *repeated_text = (char *)malloc(file_size * n + 1);
    if (!repeated_text) {
        perror("Error allocating memory for repeated text");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        memcpy(repeated_text + i * file_size, text, file_size);
    }

    repeated_text[file_size * n] = '\0';

    return repeated_text;
}
