#include "file_functions.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>

void initialize_reviews(cpd::HashTable<int,Review>& review_table,
                        const std::string file_path){

  std::ifstream afile(file_path);
  std::string line;

  if(afile.is_open()){
    int i = 0;
    int classification;
    std::string review_str;
    // Iterates through file adding each line to the list.
    while(getline(afile, line)){
      std::istringstream iss(line);

      // Extracts review classification
      iss >> classification;
      // Get review string
      review_str = iss.str().substr(2,std::string::npos);

      Review review(i, classification, review_str);
      review_table.insert(i, review);

      i++;
    }
    afile.close();
  }
}

void initialize_words(cpd::HashTable<std::string,Word>& word_table,
                      cpd::HashTable<int,Review>& review_table){
  for(auto& review : review_table){
    std::string inp = review.get_review();
    remove_copy_if(inp.begin(), inp.end(), inp.begin(), ispunct);
    std::istringstream iss(inp);
    std::string aux;

    // Iterates for each token
    while(iss){
      // Pass the token to an auxiliary string.
      iss >> aux;
      // Lowercase the word.
      transform(aux.begin(), aux.end(), aux.begin(), tolower);

      cpd::HashTable<std::string,Word>::iterator it = word_table.search(aux);

      if (it != word_table.end()){ // word already on table
        // Update word
        (*it).inc_occurrence();
        (*it).add_sum(review.get_classification());
        (*it).get_reviews().push_back(review.get_id());
      }else{
        // Create and insert new word
        Word word(aux);
        word.inc_occurrence();
        word.add_sum(review.get_classification());
        word.get_reviews().push_back(review.get_id());

        word_table.insert(aux, word);
      }
    }
  }
}

void initialize_data(cpd::HashTable<std::string,Word>& word_table,
                    cpd::HashTable<int,Review>& review_table,
                    const std::string file_path){

  initialize_reviews(review_table, file_path);
  initialize_words(word_table, review_table);
}
