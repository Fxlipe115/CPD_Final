#include "file_functions.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <iostream>

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
  }else{
    std::cerr << "Error: File \"" << file_path << "\" not found." << '\n';
    exit(-1);
  }
}

void initialize_words(cpd::HashTable<std::string,Word>& word_table,
                      cpd::HashTable<int,Review>& review_table){
  for(auto& review : review_table){
    std::string inp(review.get_review());
    //remove_copy_if(inp.begin(), inp.end(), inp.begin(), ispunct);
	  //inp.erase (std::remove_if(inp.begin(), inp.end(), ispunct), inp.end());
    // function that removes punctuation marks, digits, leading and trailing spaces and extra spaces from string 'str'
	  auto f = [](std::string str){
		  std::string s;
      str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
      str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
      bool space = false;
		  for(auto& c : str){
			  if(isalpha(c)){
				  s += c;
          space = false;
			  }else if(isspace(c) && !space){
          space = true;
          s+= ' ';
        }
		  }
		  return s;
	  };

    std::istringstream iss(f(inp));
    std::string aux;

    // Iterates for each token
    while(iss){
      // Pass the token to an auxiliary string.
      iss >> aux;

      if(aux != ""){
        // Lowercase the word.
        transform(aux.begin(), aux.end(), aux.begin(), tolower);

        cpd::HashTable<std::string,Word>::iterator it = word_table.search(aux);

        if (it != word_table.end()){ // word already on table
          // Update word
          (*it).inc_occurrence();
          (*it).add_sum(review.get_classification());
          // checks if review is already on word's inverted index
          if(review.get_classification() < 2) (*it).inc_neg();
          else (*it).inc_pos();
          // add review only if not already on the index
          if(std::find((*it).get_reviews().begin(),(*it).get_reviews().end(),review.get_id()) == (*it).get_reviews().end()){
            (*it).add_review(review.get_id());
          }
        }else{
          // Create and insert new word
          Word word(aux);
          word.inc_occurrence();
          word.add_sum(review.get_classification());
          word.add_review(review.get_id());
          if(review.get_classification() < 2) word.inc_neg();
          else word.inc_pos();

          word_table.insert(aux, word);
        }
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
