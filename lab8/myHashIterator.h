#ifndef MY_HASH_H
#define MY_HASH_H
#include <iostream>
#include "hashmap.h"
using std::cout;
using std::endl;


template<typename Key, typename T, typename Compare, typename Hash>
class myHashIterator : public HashIterator<Key, T, Compare, Hash>{
public:

  void increment(){
    cout << "fuck yeah! Increment!" << endl;
    HashIterator<Key, T, Compare, Hash>::increment();
  }
  void decrement(){
    cout << "fuck yeah! Decrement!" << endl;
    HashIterator<Key, T, Compare, Hash>::increment();
  }
};
#endif
