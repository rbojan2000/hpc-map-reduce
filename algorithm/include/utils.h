#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::string repeat_text(const std::string &text, int n);
std::string read_file(const std::string &file_path);
void print_unordered_map(const std::unordered_map<std::string, int> &word_count);

#endif
