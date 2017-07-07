#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>
#include "hash_table.hpp"
#include "review.hpp"
#include "word.hpp"
#include "file_functions.hpp"

double score(std::string& review, cpd::HashTable<std::string,Word>& word_table);

int main(int argc, char const *argv[]) {
  cpd::HashTable<int,Review> review_table;
  cpd::HashTable<std::string,Word> word_table;

  initialize_data(word_table, review_table, "./resources/movieReviews.txt");

  // for(auto& word : word_table){
  //   std::cout << "Key: " << word.get_key() << '\n';
  //   std::cout << "Sum: " << word.get_sum() << '\n';
  //   std::cout << "Occurrences: " << word.get_occurrences() << '\n';
  //   std::cout << "Mean: " << word.mean() << '\n';
  //   std::cout << '\n';
  // }

  std::string review;
  std::cin >> review;

  std::cout << score(review, word_table) << std::endl;

  return 0;
}

double score(std::string& review, cpd::HashTable<std::string,Word>& word_table){
  double score = 0;
  int i = 0;

  std::remove_copy_if(review.begin(), review.end(), review.begin(), ispunct);
  std::istringstream iss(review);
  std::string aux;

  // Iterates for each token
  while(iss){
    // Pass the token to an auxiliary string.
    iss >> aux;
    // Lowercase the word.
    transform(aux.begin(), aux.end(), aux.begin(), tolower);

    cpd::HashTable<std::string,Word>::iterator it = word_table.search(aux);

    if(it != word_table.end()){ // word found
      score += (*it).mean();
    }else{ // word not on table
      score += 2; // neutral
    }
    i++;
  }

  return score/i;
}
