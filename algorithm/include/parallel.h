#ifndef PARALLEL_H
#define PARALLEL_H

#include <hash_map.h>
#include <tokenizer.h>
#include <config.h>
#include <omp.h>

void parallel_word_count(char *text);

#endif
