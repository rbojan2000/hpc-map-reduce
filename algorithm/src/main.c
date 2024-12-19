#include <stdio.h>
#include <omp.h>
#include <serial.h>
#include <utils.h>

int main() {
    
    long file_size;
    char *text = read_file("../input-text/test.txt", &file_size);

    if (!text) {
        return 1;
    }

    #if ENABLE_DEBUG
    printf("File content (%ld bytes):\n", file_size);
    #endif

    #if SERIAL
    HashMap word_count;
    serial_word_count(text, &word_count);
    #endif
    
    #if ENABLE_DEBUG
    print_hash_map(&word_count);
    #endif

    #if PARALLEL
    printf("hello from parallel imppl");
    #endif
    
    free(text);

    return 0;
}
