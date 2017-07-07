#ifndef FILE_FUNCTIONS_HPP
#define FILE_FUNCTIONS_HPP

#include "hash_table.hpp"
#include "word.hpp"
#include "review.hpp"

void initialize_data(cpd::HashTable<std::string,Word>& word_table,
                    cpd::HashTable<int,Review>& review_table,
                    const std::string file_path);

#endif
