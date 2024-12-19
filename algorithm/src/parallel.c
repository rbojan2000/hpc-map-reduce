#include <parallel.h>

void parallel_word_count(char *text, long text_size) {
    long part_size = text_size / NUM_THREADS;
    long remainder = text_size % NUM_THREADS;

    HashMap global_word_count;
    init_hash_map(&global_word_count);


    HashMap local_word_counts[NUM_THREADS];

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        // split

        int thread_id = omp_get_thread_num();
        long start_index = thread_id * part_size + (thread_id < remainder ? thread_id : remainder);
        long end_index = start_index + part_size + (thread_id < remainder ? 1 : 0);

        if (end_index > text_size) {
            end_index = text_size;
        }

        long current_part_size = end_index - start_index;
        char *part = (char *)malloc(current_part_size + 1);

        if (!part) {
            perror("Failed to allocate memory for part");
        }

        memcpy(part, text + start_index, current_part_size);
        part[current_part_size] = '\0';

        #if ENABLE_DEBUG
        printf("Thread %d (Part %d):\n%s\n\n", thread_id, thread_id, part);
        #endif

        int token_count;
        char **tokens = tokenize(part, &token_count);

        #if ENABLE_DEBUG
        printf("Thread %d, number of tokens: %d\n", thread_id, token_count);
        #endif

        
        // map

        init_hash_map(&local_word_counts[thread_id]);

        for (int i = 0; i < token_count; i++) {
            add_word(&local_word_counts[thread_id], tokens[i]);
        }

        #if ENABLE_DEBUG
        printf("Thread %d, word count:\n", thread_id);        
        print_hash_map(&local_word_counts[thread_id]);
        #endif

        free(part);
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
}
