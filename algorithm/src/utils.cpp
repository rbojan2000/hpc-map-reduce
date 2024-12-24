#include <utils.h>

std::string read_file(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string repeat_text(const std::string &text, int n) {
    std::string repeated_text;
    for (int i = 0; i < n; ++i) {
        repeated_text += text;
    }
    return repeated_text;
}

void print_unordered_map(const std::unordered_map<std::string, int> &word_count) {
    for (const auto &entry : word_count) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}