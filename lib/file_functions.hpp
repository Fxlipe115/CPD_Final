#ifndef FILE_FUNCTIONS_HPP
#define FILE_FUNCTIONS_HPP

#include "../lib/hash_table.hpp"
#include "../lib/word.hpp"
#include "../lib/review.hpp"

void initialize_data(cdp::HashTable<std::string,Word>& word_table,
                    cdp::HashTable<int,Review>& review_table,
                    const std::string file_path)

#endif