#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <string>
#include <vector>
#include <list>
#include <stddef.h>

namespace cpd{

  template <typename T> class HashIter;

  //===============HashTable===============
  template <typename T>
  class HashTable{
    private:
      typedef std::vector<std::list<T>> Table;
      typedef std::list<T> Bucket;
      const int initialSize = 17;
      Table table;
      int tableSize;
      int occupancy;

      void resize();
      void shrinkToFit();
      // hash functions for supported types
      unsigned long hash(std::string value);
      unsigned long hash(int value);
    public:
      // iterator definitions
      friend class HashIter<T>;
      typedef HashIter<T> iterator;
      typedef ptrdiff_t difference_type;
      typedef size_t size_type;
      typedef T value_type;
      typedef T* pointer;
      typedef T& reference;
      iterator begin();
      iterator end();

      HashTable();
      int getSize();
      int getOccupancy();
      int getCollisions();
      void insert(T item);
      void remove(iterator item);
      iterator search(T item);
  };

    //===============Iterator===============
  template <typename T>
  class HashIter{
    private:
      HashTable<T>& hashTable;
      typename HashTable<T>::Table::iterator curBucket;
      typename HashTable<T>::Bucket::iterator curItem;
    public:
      HashIter(HashTable<T>& ht, bool isBegin);
      HashIter(HashTable<T>& ht,
        typename HashTable<T>::Table::iterator bucket,
        typename HashTable<T>::Bucket::iterator item);
      HashIter(const HashIter<T>& hi); // copy constructor
      typename HashTable<T>::Table::iterator getCurBucket();
      typename HashTable<T>::Bucket::iterator getCurItem();
      bool operator==(const HashIter<T>& other);
      bool operator!=(const HashIter<T>& other);
      T& operator*();
      HashIter<T>& operator++(); // prefix: ++iter
      HashIter<T> operator++ (int); //postfix: iter++
  };
}

#include "hash_table.inl"

#endif
