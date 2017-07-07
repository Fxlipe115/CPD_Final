#ifndef REVIEW_HPP
#define REVIEW_HPP

#include <string>

class Review{
private:
  int id;
  int classification;
  std::string review;

public:
  Review(int id, int classification, std::string review);
  int id();
  int classification();
  std::string review();
};

#endif
