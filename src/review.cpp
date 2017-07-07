#include "review.hpp"

Review::Review(int id, int classification, std::string review)
 : id(id), classification(classification), review(review)
{}

int Review::get_id(){
  return id;
}

int Review::get_classification(){
  return classification;
}

std::string Review::get_review(){
  return review;
}
