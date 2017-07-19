/*
 * Here the file functions are defined. The functions do things such as reading the files and
 * inserting in the hash table.
 */

#include "tsv_trainer.hpp"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <iostream>

namespace cpd{

// Reads from the file and inserts the review with the classification on the reviews table.
void TsvTrainer::initialize_reviews(HashTable<int, Review>& review_table, const std::string file_path){
    std::ifstream afile(file_path);
    std::string line;

    if(afile.is_open()){

        getline(afile,line);

        // Iterates through file adding each line to the list.
        while(getline(afile, line)){
            size_t n = line.find('\t');
            int phraseId = atoi(line.substr(0,n).c_str());
            line.erase(0,n+1);

            n = line.find('\t');
            //SentenceId
            line.erase(0,n+1);

            n = line.find('\t');
            std::string phrase = line.substr(0,n);
            line.erase(0,n+1);

            int sentiment = atoi(line.c_str());

            Review review(phraseId, sentiment, phrase);
            review_table.insert(phraseId, review);

        }
        afile.close();
    }else{
        std::cerr << "Error: File \"" << file_path << "\" not found." << '\n';
        exit(-1);
    }
}

// Builds the word table(inverted index) from the review table.
void TsvTrainer::initialize_words(HashTable<std::string, Word>& word_table,
                                  HashTable<int, Review>& review_table){
    for(auto& review : review_table){
        std::string inp(review.get_review());
        //remove_copy_if(inp.begin(), inp.end(), inp.begin(), ispunct);
        inp.erase (std::remove_if(inp.begin(), inp.end(), [](char c){return ispunct(c) || isdigit(c);}), inp.end());

        std::istringstream iss(inp);
        std::string aux;

        // Iterates for each token
        while(iss >> aux){

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

void TsvTrainer::initialize_data(HashTable<std::string,Word>& word_table,
                                 HashTable<int,Review>& review_table,
                                 const std::string file_path){

    initialize_reviews(review_table, file_path);
    initialize_words(word_table, review_table);
}

}  // namespace cpd
