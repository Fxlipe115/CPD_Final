#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <random>
#include <iterator>

namespace cpd{
  template <class RandomAccessIterator>
  void quick_sort(RandomAccessIterator first, RandomAccessIterator last){
    size_t size = std::distance(first, last);
    if(size > 1){
      // choose pivot randomly
      RandomAccessIterator pivot = first;
      std::random_device rd;
      std::advance(pivot, rd()%size);
      typename std::iterator_traits<RandomAccessIterator>::value_type val = *pivot;

      RandomAccessIterator left = first;
      RandomAccessIterator right = last;
      std::advance(right, -1);

      std::swap(*pivot, *right);
      RandomAccessIterator pivot_pos = left;

      while (left != right){
        if (*left < val){
          std::swap(*left, *pivot_pos);
          std::advance(pivot_pos, 1);
        }
        std::advance(left, 1);
      }

      std::swap(*pivot_pos, *right);

      // right = pivot_pos;
      // std::advance(right, 1);

      quick_sort(first, pivot_pos);
      quick_sort(pivot_pos, last);
    }
  }

  template <class RandomAccessIterator, class Compare>
  void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp){
    size_t size = std::distance(first, last);
    if(size > 1){
      // choose pivot randomly
      RandomAccessIterator pivot = first;
      std::random_device rd;
      std::advance(pivot, rd()%size);
      RandomAccessIterator left = first;
      RandomAccessIterator right = last;
      std::advance(right, -1);
      while(std::distance(left, right) >= 0){
        while(comp((*left), (*pivot))){
          std::advance(left, 1);
        }
        while(comp((*pivot), (*right))){
          std::advance(right, -1);
        }
        if(std::distance(left, right) >= 0){
          std::iter_swap(left, right);
          std::advance(left, 1);
          std::advance(right, -1);
        }
      }
      quick_sort(first, pivot, comp);
      quick_sort(pivot, last, comp);
    }
  }
}

#endif
