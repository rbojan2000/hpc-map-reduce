#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> tokenize(const std::string &text);
void normalize_text(std::string &text);

#endif
