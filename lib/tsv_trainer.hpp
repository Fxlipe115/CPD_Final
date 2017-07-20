#ifndef LIB_TSV_TRAINER_HPP
#define LIB_TSV_TRAINER_HPP

#include "hash_table.hpp"
#include "review.hpp"
#include "word.hpp"

namespace cpd{

class TsvTrainer{
 private:
  static void initialize_reviews(HashTable<int, Review>& review_table, const std::string file_path);
  static void initialize_words(HashTable<std::string, Word>& word_table, HashTable<int, Review>& review_table);

 public:
  static void initialize_data(HashTable<std::string,Word>& word_table,
                              HashTable<int,Review>& review_table,
                              const std::string file_path);
};
}

#endif
