// template class
#include "../lib/hash_table.hpp"

// non-template classes
#include "../lib/word.hpp"
#include "../lib/review.hpp"
#include <string>

template class cdp::HashTable<int,Review>
template class cdp::HashTable<std::string,Word>
