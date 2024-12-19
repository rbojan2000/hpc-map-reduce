#include <stdio.h>
#include <omp.h>
#include <utils.h>
#include <serial.h>
#include <parallel.h>

int main() {
    const char *filename = "../input-text/Anna-Karenina.txt";
    int n = 100;

    long text_size;
    char *text = read_file(filename, &text_size);

    char *algorithm_input_text = repeat_text(text, text_size, n);
    text_size = text_size * n;
    double start_time; 
    double end_time;
    
    #if ENABLE_DEBUG
    printf("File content (%ld bytes):\n\n", text_size);
    #endif

    #if SERIAL
    printf("Running serial implementation..\n\n");

    start_time = omp_get_wtime(); 
    serial_word_count(algorithm_input_text);
    end_time = omp_get_wtime(); 
    printf("Serial implementation took %f seconds\n", end_time - start_time);
    #endif
    

    #if PARALLEL
    printf("Running parallel implementation..\n\n");

    start_time = omp_get_wtime(); 
    parallel_word_count(algorithm_input_text, text_size);
    end_time = omp_get_wtime(); 
    printf("Parallel implementation took %f seconds\n", end_time - start_time);

    #endif
    
    free(text);
    free(algorithm_input_text);

    return 0;
}
