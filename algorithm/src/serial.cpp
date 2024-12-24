#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <serial.h>

void serial_word_count(const std::string &text) {
    std::unordered_map<std::string, int> global_word_count;

    std::string normalized_text = text;
    normalize_text(normalized_text);

    std::vector<std::string> tokens = tokenize(normalized_text);

    for (const auto &word : tokens) {
        global_word_count[word]++;
    }

    #if ENABLE_DEBUG
        std::cout << "Global Word Count Results:" << std::endl;
        print_unordered_map(global_word_count);
    #endif
}
