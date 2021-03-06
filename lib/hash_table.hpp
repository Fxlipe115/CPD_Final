#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <stddef.h>

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "review.hpp"
#include "word.hpp"

namespace cpd{

template <typename K, typename T>
class HashIter;

//===============HashTable===============
template <typename K, typename T>
class HashTable{
 private:
  typedef std::vector<std::list<std::pair<K,T> > > Table;
  typedef std::list<std::pair<K,T> > Bucket;
  const int initialSize = 17;
  Table table;
  int tableSize;
  int occupancy;

  void resize();
  void shrinkToFit();
  // hash functions for supported types
  //unsigned long hash(K value);
  unsigned long hash(std::string value);
  unsigned long hash(int value);
 public:
  // iterator definitions
  friend class HashIter<K,T>;
  typedef HashIter<K,T> iterator;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;

  // member functions
  HashTable();
  int getSize();
  int getOccupancy();
  int getCollisions();
  void insert(const K key, const T item);
  void remove(const iterator item);
  iterator search(const K key);
  iterator begin();
  iterator end();
};

  //===============Iterator===============
template <typename K, typename T>
class HashIter{
 private:
  HashTable<K,T>& hashTable;
  typename HashTable<K,T>::Table::iterator curBucket;
  typename HashTable<K,T>::Bucket::iterator curItem;
 public:
  HashIter(HashTable<K,T>& ht, bool isBegin);
  HashIter(HashTable<K,T>& ht,
           typename HashTable<K,T>::Table::iterator bucket,
           typename HashTable<K,T>::Bucket::iterator item);
  HashIter(const HashIter<K,T>& hi); // copy constructor
  typename HashTable<K,T>::Table::iterator getCurBucket();
  typename HashTable<K,T>::Bucket::iterator getCurItem();
  bool operator==(const HashIter<K,T>& other);
  bool operator!=(const HashIter<K,T>& other);
  T& operator*();
  HashIter<K,T>& operator++(); // prefix: ++iter
  HashIter<K,T> operator++ (int); //postfix: iter++
};
}  // namespace cpd

#endif
