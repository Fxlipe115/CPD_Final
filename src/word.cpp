#include<./../lib/word.hpp>

using namespace std;

Word::Word(string key)
 : sum(0), key(key), occurrences(0), reviews()
{}

double Word::mean(){
    return this->sum/this->occurrences;
}

void Word::set_sum(double sum){
    this->sum = sum;
}

void Word::add_sum(double value){
    this->sum += value;
}

void Word::set_occurrences(int occ){
    this->occurrences = occ;
}

void Word::inc_occurrence(){
    this->occurrences++;
}

void Word::set_key(string key){
    this->key = key;
}

double Word::get_sum(){
    return this->sum;
}

string Word::get_key(){
    return this->key;
}

int Word::get_occurrences(){
    return this->occurrences;
}

std::list<int> reviews(){
    return reviews
}
