#include <cmath>
#include <algorithm>

//===============HashTable===============
template <typename K, typename T>
cpd::HashTable<K,T>::HashTable()
   : table(initialSize,Bucket()), tableSize(initialSize), occupancy(0)
{}

template <typename K, typename T>
void cpd::HashTable<K,T>::resize(){
  tableSize = tableSize * 2 + 1;

  Table aux(table); // copy of current table

  table.clear();
  table.resize(tableSize,Bucket());

  occupancy = 1;

  for(Bucket& bucket : aux){
    for(auto& tup : bucket)
      insert(tup.first, tup.second);
  }
}

template <typename K, typename T>
void cpd::HashTable<K,T>::shrinkToFit(){
  //TODO
}

template <typename K, typename T>
unsigned long cpd::HashTable<K,T>::hash(std::string value){
  unsigned long hashValue = (int)(value[0]);
  int len = value.size();
  int i = 0;

  for(auto& c : value){
    hashValue += (int)pow((int)c,i) % (int)(pow(2,len)+1);
    i++;
  }

  return hashValue;
}

template <typename K, typename T>
unsigned long cpd::HashTable<K,T>::hash(int value){
  return hash(std::to_string(value));
}

template <typename K, typename T>
int cpd::HashTable<K,T>::getSize(){
  return tableSize;
}

template <typename K, typename T>
int cpd::HashTable<K,T>::getOccupancy(){
  return occupancy;
}

template <typename K, typename T>
int cpd::HashTable<K,T>::getCollisions(){
  int collisions = 0;
  for(auto& bucket : table){
    if(bucket.size() > 1){
        collisions += bucket.size() - 1;
    }
  }

  return collisions;
}

template <typename K, typename T>
void cpd::HashTable<K,T>::insert(const K key, const T item){
  occupancy++;
  if(occupancy > (3 * (int)(tableSize / 4))){
    resize();
  }
  //std::pair<K,T> tup = {key, item};
  table[hash(key) % tableSize].push_back(make_pair(key,item));
}

template <typename K, typename T>
void cpd::HashTable<K,T>::remove(iterator item){
  (*item.getCurBucket()).erase(item.getCurItem());
  occupancy--;
}

template <typename K, typename T>
typename cpd::HashTable<K,T>::iterator cpd::HashTable<K,T>::search(const K key, const T item){
  typename Table::iterator bucket = table.begin() + (hash(key) % tableSize);

  typename Bucket::iterator it = std::find((*bucket).begin(),(*bucket).end(),make_pair(key,item));

  if(it != (*bucket).end()){
    return iterator(*this, bucket, it);
  }else{
    return end();
  }
}

template <typename K, typename T>
typename cpd::HashTable<K,T>::iterator cpd::HashTable<K,T>::begin(){
  return iterator(*this, true);
}

template <typename K, typename T>
typename cpd::HashTable<K,T>::iterator cpd::HashTable<K,T>::end(){
  return iterator(*this, false);
}

//===============Iterator===============
template <typename K, typename T>
cpd::HashIter<K,T>::HashIter(HashTable<K,T>& ht, bool isBegin)
 : hashTable(ht){
  if(isBegin){ // begin iterator
    curBucket = hashTable.table.begin();
    bool flag = true;
    while(flag){
      if(curBucket != hashTable.table.end()){
        if((*curBucket).empty()){
          curBucket++;
        }else{ // found first non-empty bucket
          flag = false;
        }
      }else{ // empty table
        flag = false;
        curBucket--;
      }
      curItem = (*curBucket).begin();
    }
  }else{ // end iterator
    curBucket = --hashTable.table.end();
    curItem = (*curBucket).end();
  }
}

template <typename K, typename T>
cpd::HashIter<K,T>::HashIter(HashTable<K,T>& ht,
  typename HashTable<K,T>::Table::iterator bucket,
  typename HashTable<K,T>::Bucket::iterator item)
 : hashTable(ht), curBucket(bucket), curItem(item)
{}

template <typename K, typename T>
cpd::HashIter<K,T>::HashIter(const HashIter<K,T>& hi) // copy constructor
 : hashTable(hi.hashTable),
   curBucket(hi.curBucket), curItem(hi.curItem)
{}

template <typename K, typename T>
typename cpd::HashTable<K,T>::Table::iterator cpd::HashIter<K,T>::getCurBucket(){
  return curBucket;
}

template <typename K, typename T>
typename cpd::HashTable<K,T>::Bucket::iterator cpd::HashIter<K,T>::getCurItem(){
  return curItem;
}

template <typename K, typename T>
bool cpd::HashIter<K,T>::operator==(const HashIter<K,T>& other){
  // bool sameHashTable = this->hashTable == other.hashTable;
  bool sameBucket = this->curBucket == other.curBucket;
  bool sameItem = this->curItem == other.curItem;
  return sameBucket && sameItem;
}

template <typename K, typename T>
bool cpd::HashIter<K,T>::operator!=(const HashIter<K,T>& other){
  return !(*this == other);
}

template <typename K, typename T>
T& cpd::HashIter<K,T>::operator*(){
  return (*curItem).second;
}

template <typename K, typename T>
cpd::HashIter<K,T>& cpd::HashIter<K,T>::operator++(){ // prefix: ++iter
  ++curItem;
  if(curItem == (*curBucket).end()){
    ++curBucket;
    bool flag = true;
    while(flag){
      if(curBucket != hashTable.table.end()){
        if((*curBucket).empty()){
          curBucket++;
          // curItem = (*curBucket).begin();
        }else{ // found non-empty bucket
          flag = false;
          curItem = (*curBucket).begin();
        }
      }else{ // end of table
        flag = false;
        curBucket--;
        curItem = (*curBucket).end();
      }
    }
  }
  return *this;
}

template <typename K, typename T>
cpd::HashIter<K,T> cpd::HashIter<K,T>::operator++(int){ //postfix: iter++
  HashIter<K,T> clone(*this);
  ++curItem;
  if(curItem == (*curBucket).end()){
    ++curBucket;
    bool flag = true;
    while(flag){
      if(curBucket != hashTable.table.end()){
        if((*curBucket).empty()){
          curBucket++;
          // curItem = (*curBucket).begin();
        }else{ // found non-empty bucket
          flag = false;
          curItem = (*curBucket).begin();
        }
      }else{ // end of table
        flag = false;
        curBucket--;
        curItem = (*curBucket).end();
      }
    }
  }
  return clone;
}
