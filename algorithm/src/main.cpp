#include <config.h>
#include <parallel.h>
#include <serial.h>

int main() {
    std::string text = read_file(FILE_PATH);
    std::string repeated_text = repeat_text(text, N);
    double start_time, end_time;

    #if ENABLE_DEBUG
        std::cout << "Repeated Text (" << N << " times):\n" <<  std::endl;
    #endif

    #if SERIAL
        std::cout << "Running SERIAL implementation ... " << std::endl;
        start_time = omp_get_wtime(); 
        serial_word_count(repeated_text);
        end_time = omp_get_wtime(); 
        std::cout << "SERIAL implementation took "<< end_time - start_time << " seconds" << std::endl;
    #endif


    #if PARALLEL
        std::cout << "Running PARALLEL implementation ... " << std::endl;
        start_time = omp_get_wtime(); 
        parallel_word_count(repeated_text);
        end_time = omp_get_wtime(); 
        std::cout << "Parallel implementation took "<< end_time - start_time << " seconds" << std::endl;
    #endif

    return 0;
}