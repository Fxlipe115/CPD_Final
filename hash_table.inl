#include <cmath>
#include <algorithm>

//===============HashTable===============
template <typename T>
cpd::HashTable<T>::HashTable()
   : table(initialSize,Bucket()), tableSize(initialSize), occupancy(0)
{}

template <typename T>
void cpd::HashTable<T>::resize(){
  tableSize = tableSize * 2 + 1;

  Table aux(table); // copy of current table

  table.clear();
  table.resize(tableSize,Bucket());

  occupancy = 1;

  for(Bucket& bucket : aux){
    for(T& i : bucket)
      insert(i);
  }
}

template <typename T>
void cpd::HashTable<T>::shrinkToFit(){
  //TODO
}

template <typename T>
unsigned long cpd::HashTable<T>::hash(std::string value){
  unsigned long hashValue = (int)(value[0]);
  int len = value.size();
  int i = 0;

  for(auto& c : value){
    hashValue += (int)pow((int)c,i) % (int)(pow(2,len)+1);
    i++;
  }

  return hashValue;
}

template <typename T>
unsigned long cpd::HashTable<T>::hash(int value){
  return hash(std::to_string(value));
}

template <typename T>
int cpd::HashTable<T>::getSize(){
  return tableSize;
}

template <typename T>
int cpd::HashTable<T>::getOccupancy(){
  return occupancy;
}

template <typename T>
int cpd::HashTable<T>::getCollisions(){
  int collisions = 0;
  for(auto& bucket : table){
    if(bucket.size() > 1){
        collisions += bucket.size() - 1;
    }
  }

  return collisions;
}

template <typename T>
void cpd::HashTable<T>::insert(T item){
  occupancy++;
  if(occupancy > (3 * (int)(tableSize / 4))){
    resize();
  }
  table[hash(item) % tableSize].push_back(item);
}

template <typename T>
void cpd::HashTable<T>::remove(iterator item){
  (*item.getCurBucket()).erase(item.getCurItem());
  occupancy--;
}

template <typename T>
typename cpd::HashTable<T>::iterator cpd::HashTable<T>::search(T item){
  typename Table::iterator bucket = table.begin() + (hash(item) % tableSize);

  typename Bucket::iterator it = std::find((*bucket).begin(),(*bucket).end(),item);

  if(it != (*bucket).end()){
    return iterator(*this, bucket, it);
  }else{
    return end();
  }
}

template <typename T>
typename cpd::HashTable<T>::iterator cpd::HashTable<T>::begin(){
  return iterator(*this, true);
}

template <typename T>
typename cpd::HashTable<T>::iterator cpd::HashTable<T>::end(){
  return iterator(*this, false);
}

//===============Iterator===============
template <typename T>
cpd::HashIter<T>::HashIter(HashTable<T>& ht, bool isBegin)
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

template <typename T>
cpd::HashIter<T>::HashIter(HashTable<T>& ht,
  typename HashTable<T>::Table::iterator bucket,
  typename HashTable<T>::Bucket::iterator item)
 : hashTable(ht), curBucket(bucket), curItem(item)
{}

template <typename T>
cpd::HashIter<T>::HashIter(const HashIter<T>& hi) // copy constructor
 : hashTable(hi.hashTable),
   curBucket(hi.curBucket), curItem(hi.curItem)
{}

template <typename T>
typename cpd::HashTable<T>::Table::iterator cpd::HashIter<T>::getCurBucket(){
  return curBucket;
}

template <typename T>
typename cpd::HashTable<T>::Bucket::iterator cpd::HashIter<T>::getCurItem(){
  return curItem;
}

template <typename T>
bool cpd::HashIter<T>::operator==(const HashIter<T>& other){
  // bool sameHashTable = this->hashTable == other.hashTable;
  bool sameBucket = this->curBucket == other.curBucket;
  bool sameItem = this->curItem == other.curItem;
  return sameBucket && sameItem;
}

template <typename T>
bool cpd::HashIter<T>::operator!=(const HashIter<T>& other){
  return !(*this == other);
}

template <typename T>
T& cpd::HashIter<T>::operator*(){
  return *curItem;
}

template <typename T>
cpd::HashIter<T>& cpd::HashIter<T>::operator++(){ // prefix: ++iter
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

template <typename T>
cpd::HashIter<T> cpd::HashIter<T>::operator++(int){ //postfix: iter++
  HashIter<T> clone(*this);
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
