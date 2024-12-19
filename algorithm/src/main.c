#include <stdio.h>
#include <omp.h>
#include <utils.h>
#include <serial.h>
#include <parallel.h>

int main() {
    const char *filename = "../input-text/test.txt";
    int n = 1;

    long text_size;
    char *text = read_file(filename, &text_size);

    char *algorithm_input_text = repeat_text(text, text_size, n);
    text_size = text_size * n;

    #if ENABLE_DEBUG
    printf("File content (%ld bytes):\n\n", text_size);
    #endif

    #if SERIAL
    HashMap word_count;
    printf("Running serial implementation..\n\n");

    serial_word_count(algorithm_input_text, &word_count);

        #if ENABLE_DEBUG
        print_hash_map(&word_count);
        #endif

    #endif
    

    #if PARALLEL
    HashMap word_count;
    printf("Running parallel implementation..\n\n");
    parallel_word_count(algorithm_input_text, text_size);

    #endif
    
    free(text);
    free(algorithm_input_text);

    return 0;
}
