#include <parallel.h>

std::vector<std::pair<size_t, size_t>> calculate_thread_indices(const std::string &text) {
    size_t text_size = text.size();
    size_t chunk_size = text_size / NUM_THREADS;

    std::vector<std::pair<size_t, size_t>> thread_indices(NUM_THREADS);

    size_t current_start = 0;

    for (int thread_id = 0; thread_id < NUM_THREADS; ++thread_id) {
        size_t start_index = current_start;
        size_t end_index = current_start + chunk_size;
        
        if (thread_id == NUM_THREADS - 1) {
            end_index = text_size;
        }

        if (end_index < text_size) {
            while (end_index < text_size && !std::isspace(static_cast<unsigned char>(text[end_index]))) {
                end_index++;
            }
        }

        thread_indices[thread_id] = {start_index, end_index};
        current_start = end_index;
    }

    return thread_indices;
}


void parallel_word_count(const std::string &text) {

    // split
    std::vector<std::pair<size_t, size_t>> thread_indices = calculate_thread_indices(text);
    std::vector<std::unordered_map<std::string, int>> local_word_counts(NUM_THREADS);

    #pragma omp parallel num_threads(NUM_THREADS)
    {  
        int thread_id = omp_get_thread_num();
        size_t start_index = thread_indices[thread_id].first;
        size_t end_index = thread_indices[thread_id].second;

        std::string part = text.substr(start_index, end_index - start_index);

        normalize_text(part);
        std::vector<std::string> tokens = tokenize(part);


        #if ENABLE_DEBUG
            std::cout << "Thread " << thread_id
                        << ": start_index = " << start_index
                        << ", end_index = " << end_index
                        << ", tokens = " << tokens.size()
                        << ", text = \"" << part << "\"" << std::endl;
        #endif

        // map

        for (const auto &word : tokens) {
            #pragma omp critical
            {
                local_word_counts[thread_id][word]++;
            }
        }

        #if ENABLE_DEBUG
            std::cout << "Thread " << thread_id << " local count" << std::endl;
            print_unordered_map(local_word_counts[thread_id]);
            std::cout << std::endl;
        #endif
    }

    // reduce

    std::unordered_map<std::string, int> global_word_count;

    #pragma omp parallel for
    for (int i = 0; i < NUM_THREADS; i++) {
        for (const auto &entry : local_word_counts[i]) {
            #pragma omp critical
            {
                global_word_count[entry.first] += entry.second;
            }
        }
    }

    #if ENABLE_DEBUG
        std::cout << "Global count" << std::endl;
        print_unordered_map(global_word_count);
    #endif
}
