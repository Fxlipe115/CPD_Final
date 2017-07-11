#include "word.hpp"
#include <cmath>

using namespace std;

Word::Word(string key)
 : sum(0), key(key), occurrences(0), pos(0), neg(0), reviews()
{}

double Word::mean(){
    // Not really your average mean
    double temp = (this->sum/this->occurrences) - 2;
    if(temp < 2){
        temp *= wil_lower_bound(this->get_neg(), this->get_occurrences());
        temp += 2;
    }
    else{
        temp *= wil_lower_bound(this->get_pos(), this->get_occurrences());
        temp += 2;
    }
    return temp;
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

const std::list<int>& Word::get_reviews(){
    return reviews;
}

void Word::add_review(int key) {
	this->reviews.push_back(key);
}

void Word::set_pos(int pos){
    this->pos = pos;
}

void Word::inc_pos(){
    this->pos++;
}

int Word::get_pos(){
    return this->pos;
}

void Word::set_neg(int neg){
    this->neg = neg;
}

void Word::inc_neg(){
    this->neg++;
}

int Word::get_neg(){
    return this->neg;
}

double Word::wil_lower_bound(int pos, int total){
    if(total == 0)
        return 0;
    else{
        double z = 1.96, phat = 1.0*pos/total;
        return (phat + z*z/(2*total) - z * sqrt((phat*(1-phat)+z*z/(4*total))/total))/(1+z*z/total);
    }
}
