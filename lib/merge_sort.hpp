#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>
#include <iterator>
#include <random>

namespace cpd{

template <class BidirectionalIterator>
void merge_sort(BidirectionalIterator first, BidirectionalIterator last){
  if(std::distance(first, last) > 1){
    BidirectionalIterator middle = first;
    std::advance(middle, std::distance(first, last) / 2);
    merge_sort(first, middle);
    merge_sort(middle, last);
    std::inplace_merge(first, middle, last);
  }
}

template <class BidirectionalIterator, class Compare>
void merge_sort(BidirectionalIterator first, BidirectionalIterator last, Compare comp){
  if(std::distance(first, last) > 1){
    BidirectionalIterator middle = first;
    std::advance(middle, std::distance(first, last) / 2);
    merge_sort(first, middle, comp);
    merge_sort(middle, last, comp);
    std::inplace_merge(first, middle, last, comp);
  }
}
}  // namespace cpd

#endif
