#ifndef PARALLEL_H
#define PARALLEL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <omp.h>
#include <tokenizer.h>
#include <config.h>
#include <utils.h>

void parallel_word_count(const std::string &text);

#endif
