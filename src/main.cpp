// Main function and others specific to be used with >this< main function aka no reason to put it in
// another file.
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <ctime>
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
double wil_lower_bound(int pos, int total);

int main(int argc, char const *argv[]) {
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

    std::cout << "Loading data..." << '\n';
    clock_t begin = clock();

    initialize_data(word_table, review_table, argv[1]);

    clock_t end = clock();
    std::cout << "Loading took " << double(end - begin) / CLOCKS_PER_SEC << " seconds." << '\n';

    int opt = 0;

    do {
        std::cout << "Choose an option:" << '\n';
        std::cout << "1 - Write new review" << '\n';
        std::cout << "2 - Evaluate reviews from file" << '\n';
        std::cout << "3 - Search reviews containing some word" << '\n';
        std::cout << "4 - Show rankings" << '\n';
        std::cout << "0 - Exit" << '\n';

        std::cout << ">> ";
        std::cin >> opt;

        switch (opt) {
            case 1:
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                show_score(word_table);
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                break;
            case 2:
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                from_file(word_table);
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                break;
            case 3:
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                show_reviews(review_table, word_table);
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                break;
            case 4:
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                show_rankings(word_table);
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                break;
            case 0:
                break;
            default:
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
                std::cerr << "Error: Invalid option." << '\n';
                std::cout << '\n';
                std::cout << "====================================================" << '\n';
                std::cout << '\n';
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
    std::string feels[] = {"Negative", "Somewhat negative", "Neutral", "Somewhat positive", "Positive"};

    std::cout << "Enter review: ";
    std::cin.ignore();
    std::getline(std::cin, review);

    double score_value = score(review, word_table);
    std::cout << "Score: " << score_value << ". \"" << feels[(int)round(score_value)] << "\"." << std::endl;
}

void show_reviews(cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table){
    std::cout << "Enter word: ";
    std::string word;
    std::cin >> word;

    int opt = 0;

    std::cout << "Filter reviews?" << '\n';
    std::cout << "1 - Show only positive reviews" << '\n';
    std::cout << "2 - Show only somewhat positive reviews" << '\n';
    std::cout << "3 - Show only neutral" << '\n';
    std::cout << "4 - Show only somewhat negative reviews" << '\n';
    std::cout << "5 - Show only negative reviews" << '\n';
    std::cout << "0 - Do not filter" << '\n';

    bool filter = false;
    int filter_key = 0;

    do {
        std::cout << ">> ";
        std::cin >> opt;

        switch (opt) {
            case 1:
                filter = true;
                filter_key = 4;
                break;
            case 2:
                filter = true;
                filter_key = 3;
                break;
            case 3:
                filter = true;
                filter_key = 2;
                break;
            case 4:
                filter = true;
                filter_key = 1;
                break;
            case 5:
                filter = true;
                filter_key = 0;
                break;
            case 0:
                break;
            default:
                std::cerr << "Error: Invalid option." << '\n';
                opt = -1;
                break;
        }

    } while(opt == -1);

    std::list<Review> l;
    reviews_containing(word,l,review_table,word_table);

    std::cout << '\n';

    int i = 1;
    for(auto& x : l){

        std::string review = x.get_review();
        double review_score = score(review,word_table);

        if(!filter || (filter && (round(review_score) == filter_key))){
            std::cout << i << ": " << review << std::endl;
            std::cout << "\tScore: " << review_score << std::endl;
            i++;
        }
    }

    if(i == 1){
        std::cout << "Query returned no results." << '\n';
    }
}

void from_file(cpd::HashTable<std::string,Word>& word_table){
    std::string file_path;
    std::cout << "Enter input file path:  ";
    std::cin >> file_path;

    std::ifstream input_file(file_path);
    if(input_file.is_open()){

        std::string out_path = file_path;
        out_path += ".out";
        std::ofstream output_file(out_path);

        if(output_file.is_open()){
            std::string review;
            std::string feels[] = {"Negative", "Somewhat negative", "Neutral", "Somewhat positive", "Positive"};

            int i = 1;
            while(getline(input_file,review)){

                output_file << i << ": " << review << std::endl;
                double score_value = score(review, word_table);
                output_file << "   Score: " << score_value << ". \"" << feels[(int)round(score_value)] << "\"." << std::endl;

                i++;
            }
            input_file.close();
            std::cout << "File \"" << out_path << "\" created successfully." << std::endl;
        }
        else{
            std::cerr << "Error: Could not create \"" << file_path << "\"." << '\n';
        }
        input_file.close();
    }
    else{
        std::cerr << "Error: File \"" << file_path << "\" not found." << '\n';
    }
}

void show_rankings(cpd::HashTable<std::string,Word>& word_table){
    int opt = 0;
    bool exit = false;

    while(!exit){
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1 - Top positive words" << std::endl;
        std::cout << "2 - Top negative words" << std::endl;
        std::cout << "3 - Most frequent words" << std::endl;
        std::cout << "0 - Cancel" << std::endl;

        std::cout << ">> ";
        std::cin >> opt;

        bool (*comp)(Word*, Word*) = nullptr;

        switch (opt){
            case 1:
                comp = [](Word* a, Word* b){return a->mean() > b->mean();};
                break;
            case 2:
                comp = [](Word* a, Word* b){return a->mean() < b->mean();};
                break;
            case 3:
                comp = [](Word* a, Word* b){return a->get_occurrences() > b->get_occurrences();};
                break;
            case 0:
                exit = true;
                break;
            default:
                std::cerr << "\tError: Invalid option." << '\n';
                break;
        }

        if(comp != nullptr){
            int k = 0;
            std::cout << "Number of words to show: ";
            std::cin >> k;

            std::list<Word*> l;
            for(auto& word : word_table){
                l.push_back(&word);
            }
            cpd::merge_sort(l.begin(), l.end(), comp);

            int i = 0;
            for(std::list<Word*>::iterator it = l.begin(); (it != l.end()) && (i < k); it++){
                std::cout << i+1 << ": \"" << (*it)->get_key() << "\" - Score: " << (*it)->mean() << ". - " << (*it)->get_occurrences() << " occurrence(s)." << '\n';
                i++;
            }

            exit = true;
        }
    }
}

double score(std::string& review, cpd::HashTable<std::string,Word>& word_table){
    double score = 0;
    int i = 0;
    std::string review_aux(review);
    //std::remove_copy_if(review_aux.begin(), review_aux.end(), review_aux.begin(), ispunct);
    //review_aux.erase (std::remove_if(review_aux.begin(), review_aux.end(), ispunct), review_aux.end());
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

    std::istringstream iss(f(review_aux));
    std::string aux;

    // Iterates for each token
    // Pass stream to string
    while(iss >> aux){
        // Lowercase the word.
        transform(aux.begin(), aux.end(), aux.begin(), tolower);

        cpd::HashTable<std::string,Word>::iterator it = word_table.search(aux);

        if(it != word_table.end()){ // word found
            score += (*it).mean();
            // word not on table
        }else{
            score += 2; // neutral
        }
        i++;
    }
    return score/i;
}

void reviews_containing(const std::string& word, std::list<Review>& output, cpd::HashTable<int,Review>& review_table, cpd::HashTable<std::string,Word>& word_table){
    //std::remove_copy_if(key.begin(), key.end(), key.begin(), ispunct);
    //key.erase (std::remove_if(key.begin(), key.end(), ispunct), key.end());
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

    std::string key = f(word);

    transform(key.begin(), key.end(), key.begin(), tolower);

    output.clear();

    cpd::HashTable<std::string,Word>::iterator itw = word_table.search(key);

    if(itw != word_table.end()){
        for(auto& i : (*itw).get_reviews()){
            cpd::HashTable<int,Review>::iterator itr = review_table.search(i);
            if(itr != review_table.end()){
                output.push_back(*itr);
            }
        }
    }
}
