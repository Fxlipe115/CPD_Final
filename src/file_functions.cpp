#include "../lib/file_functions.hpp"
#include<fstream>
#include<algorithm>
#include<sstream>
#include<string>

// using namespace std;
//
// list<string> read_file(string file_path){
//     // Reads a file from file_path and returns its contents in the list called "ret".
//     list<string> ret;
//     string line;
//     ifstream afile(file_path);
//
//     if(afile.is_open()){
//         // Iterates through file adding each line to the list.
//         while(getline(afile, line)) ret.push_back(line);
//         afile.close();
//     }
//
//     return ret;
// }
//
// list<string> tokenize(string inp){
//     // Takes a string and returns a list of its tokens, works like split() method from Python.
//     // Remove punctiation.
//     remove_copy_if(inp.begin(), inp.end(), ispunct);
//     istringstream iss(inp);
//     string aux;
//     list<string> ret;
//
//     // Iterates for each token
//     while(iss){
//         // Pass the token to an auxiliary string.
//         iss >> aux;
//         // Lower case the string.
//         transform(aux.begin(), aux.end(), aux.begin(), tolower);
//         ret.push_back(aux);
//     }
//
//     return ret;
// }

void initialize_reviews(cdp::HashTable<int,Review>& review_table,
                        const std::string file_path){

  ifstream afile(file_path);
  std::string line;

  if(afile.is_open()){
    int i = 0;
    int classification;
    std::string review_str;
    // Iterates through file adding each line to the list.
    while(getline(afile, line)){
      istringstream iss(line);

      // Extracts review classification
      iss >> classification;
      // Get review string
      review_str = iss.str();

      Review review(i, classification, review_str);
      review_table.insert(i, review);

      i++;
    }
    afile.close();
  }
}

void initialize_words(cdp::HashTable<std::string,Word>& word_table,
                      cdp::HashTable<int,Review>& review_table){
  for(auto& review : review_table){
    std::string inp = review.review();
    remove_copy_if(inp.begin(), inp.end(), ispunct);
    istringstream iss(inp);
    string aux;

    // Iterates for each token
    while(iss){
      // Pass the token to an auxiliary string.
      iss >> aux;
      // Lowercase the word.
      transform(aux.begin(), aux.end(), aux.begin(), tolower);

      cpd::HashTable::iterator it = word_table.search(aux);

      if (it != word_table.end()){ // word already on table
        // Update word
        (*it).inc_occurrence();
        (*it).add_sum(review.classification());
        (*it).reviews().push_back(review.id());
      }else{
        // Create and insert new word
        Word word(aux);
        word.inc_occurrence();
        word.add_sum(review.classification());
        word.reviews().push_back(review.id());

        word_table.insert(aux, word)
      }
    }
  }
}

void initialize_data(cdp::HashTable<std::string,Word>& word_table,
                    cdp::HashTable<int,Review>& review_table,
                    const std::string file_path){

  initialize_reviews(review_table, file_path);
  initialize_words(word_table, review_table);
}
