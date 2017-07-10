#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <list>
#include "hash_table.hpp"
#include "review.hpp"
#include "word.hpp"
#include "file_functions.hpp"
#include "merge_sort.hpp"

void main_program(int argc, char const *argv[]);
void help(int argc, char const *argv[]);
void usage(int argc, char const *argv[]);
void show_score(cpd::HashTable<std::string,Word>& word_table);
void from_file(cpd::HashTable<std::string,Word>& word_table);
void show_reviews(cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table);
void show_rankings(cpd::HashTable<std::string,Word>& word_table);
double score(std::string& review, cpd::HashTable<std::string,Word>& word_table);
void reviews_containing(const std::string& word, std::list<Review>& output, cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table);

int main(int argc, char const *argv[]) {

  // std::list<int> l = {5,1,6,2,3,8,7,4};
  // cpd::merge_sort(l.begin(), l.end(), [](int a, int b){return a > b;});
  // for(auto& i : l){
  //   std::cout << i << '\n';
  // }

  if (argc == 2) {
    if (std::string(argv[1]) == "-h") {
      help(argc,argv);
    } else if(argv[1][0] == '-') {
      usage(argc,argv);
    } else {
      main_program(argc,argv);
    }
  } else if (argc == 3) {
    if (std::string(argv[1]) == "-h" || std::string(argv[2]) == "-h") {
      help(argc,argv);
    } else {
      usage(argc,argv);
    }
  } else {
    usage(argc,argv);
  }

  return 0;
}

void main_program(int argc, char const *argv[]){

  cpd::HashTable<int,Review> review_table;
  cpd::HashTable<std::string,Word> word_table;

  initialize_data(word_table, review_table, argv[1]);

  int opt = 0;

  do {
    std::cout << "Choose an option:" << '\n';
    std::cout << "1 - Write new review" << '\n';
    std::cout << "2 - Evaluate reviews from file" << '\n';
    std::cout << "3 - Search reviews containing some word" << '\n';
    std::cout << "4 - Show rankings" << '\n';
    std::cout << "0 - Exit" << '\n';

    std::cout << ">  ";
    std::cin >> opt;
    // std::cin.clear();
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opt) {
      case 1:
        show_score(word_table);
        break;
      case 2:
        //from_file();
        break;
      case 3:
        show_reviews(review_table, word_table);
        break;
      case 4:
        //show_rankings();
      case 0:
        break;
    }

  } while(opt != 0);
}

void help(int argc, char const *argv[]){
  usage(argc,argv);
  std::cout << "Arguments:" << '\n';
  std::cout << "\tpath\tPath to reviews file." << '\n';
  std::cout << '\n';
  std::cout << "Options:" << '\n';
  std::cout << "\t-h\tShow this message." << '\n';
  std::cout << '\n';
}

void usage(int argc, char const *argv[]){
  std::cout << "Usage: " << argv[0] << " file [-h]" << '\n';
}

void show_score(cpd::HashTable<std::string,Word>& word_table){
  std::string review;
  std::getline(std::cin, review);
  std::cout << score(review, word_table) << std::endl;
}

void show_reviews(cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table){
  std::string word;
  std::cin >> word;

  std::list<Review> l;
  reviews_containing(word,l,review_table,word_table);
  int i = 1;
  for(auto& x : l){
     std::cout << i << ": " << x.get_review() << std::endl;
     i++;
  }
}

void from_file(cpd::HashTable<std::string,Word>& word_table){
  std::string file_path;
  std::cout << "Enter input file path:  ";
  std::cin >> file_path;

  ifstream input_file(file_path,ios::in);
  if(input_file.is_open()){
    string review;
    while(getline(myfile,buffer)){
      std::cout << score(review, word_table) << std::endl;
    }
      input_file.close();
    }
  else{
    std::cerr << "Error: File \"" << file_path << "\" not found." << '\n';
  }
}

void show_rankings(cpd::HashTable<std::string,Word>& word_table){
  std::cout << "\tChoose an option" << std::endl;
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

void reviews_containing(const std::string& word, std::list<Review>& output, cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table){
	std::string key = word;
	std::remove_copy_if(key.begin(), key.end(), key.begin(), ispunct);
	transform(key.begin(), key.end(), key.begin(), tolower);

  output.clear();

	cpd::HashTable<std::string,Word>::iterator itw = word_table.search(key);

	if(itw != word_table.end()){
		for(auto& i : (*itw).get_reviews()){
			cpd::HashTable<int,Review>::iterator itr = review_table.search(i);
			output.push_back(*itr);
		}
	}
}
