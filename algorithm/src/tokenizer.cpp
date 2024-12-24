#include <tokenizer.h>

std::vector<std::string> tokenize(const std::string &text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void normalize_text(std::string &text) {
    std::string normalized;
    for (char ch : text) {
        if (!std::ispunct(static_cast<unsigned char>(ch)) && ch != '\n') {
            normalized += std::tolower(static_cast<unsigned char>(ch));
        } else if (std::isspace(static_cast<unsigned char>(ch))) {
            normalized += ' ';
        }
    }
    text = normalized;
}