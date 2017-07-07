#include "../lib/review.hpp"

Review::Review(int id, int classification, std::string review)
 : id(id), classification(classification), review(review)
{}

int Review::id(){
  return review;
}

int Review::classification(){
  return classification;
}

std::string Review::review(){
  return review;
}
