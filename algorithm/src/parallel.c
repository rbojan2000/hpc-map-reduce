#include <parallel.h>

void parallel_word_count(char *text) {

    int token_count;
    char **tokens = tokenize(text, &token_count);

    #if ENABLE_DEBUG
    printf("Number of tokens %d:\n", token_count);
    #endif

    HashMap global_word_count;
    init_hash_map(&global_word_count);

    int part_size = token_count / NUM_THREADS;

    HashMap local_word_counts[NUM_THREADS];

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        // split
        int thread_id = omp_get_thread_num();

        int start_index = thread_id * part_size;
        int end_index;
        if (thread_id == NUM_THREADS - 1) {
            end_index = token_count;
        } else {
            end_index = start_index + part_size;
        }

        #if ENABLE_DEBUG
        printf("Thread %d, number of tokens %d:\n", thread_id, end_index-start_index);
        #endif

        // map
        init_hash_map(&local_word_counts[thread_id]);

        for (long i = start_index; i < end_index; i++) {
            add_word(&local_word_counts[thread_id], tokens[i]);
        }
    }

    // reduce
    #pragma omp parallel for
    for (int i = 0; i < NUM_THREADS; i++) {
        for (int j = 0; j < HASH_SIZE; j++) {
            if (local_word_counts[i].hash_table[j].count > 0) {
                #pragma omp critical
                {
                    add_word(&global_word_count, local_word_counts[i].hash_table[j].word);
                }
            }
        }
    }

    #if ENABLE_DEBUG
    printf("\n\nGlobal word count:\n");
    print_hash_map(&global_word_count);
    #endif

    for (int i = 0; i < token_count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
