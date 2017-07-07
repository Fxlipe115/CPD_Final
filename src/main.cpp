#include <iostream>
#include "../src/hash_table_inst.cpp"
#include "../lib/review.hpp"
#include "../lib/word.hpp"
#include "../lib/file_functions.hpp"

double score(std::string review, cpd::HashTable<std::string,Word> word_table);

int main(int argc, char const *argv[]) {
  cpd::HashTable<int,Review> review_table;
  cpd::HashTable<std::string,Word> word_table;

  initialize_data(word_table, review_table, "./resources/movieReviews.txt");

  std::string review;
  std::cin >> review;

  std::cout << score(review, word_table) << std::endl;

  return 0;
}

double score(std::string review, cpd::HashTable<std::string,Word> word_table){
  score = 0;
  i = 0;

  remove_copy_if(review.begin(), review.end(), ispunct);
  istringstream iss(review);
  string aux;

  // Iterates for each token
  while(iss){
    // Pass the token to an auxiliary string.
    iss >> aux;
    // Lowercase the word.
    transform(aux.begin(), aux.end(), aux.begin(), tolower);

    cpd::HashTable::iterator it = word_table.search(aux);

    if(it != word_table.end()){ // word found
      score += (*it).mean();
    }else{ // word not on table
      score += 2; // neutral
    }
    i++;
}
