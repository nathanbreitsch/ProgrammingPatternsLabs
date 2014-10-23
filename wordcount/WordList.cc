#include "WordList.h"
#include <algorithm>
#include <iostream>
#define INITIAL_CAP 16

using std::endl;
using std::cout;

WordList::WordList(){
    size_ = 0;
    capacity_ = INITIAL_CAP;
    wordArray_ = new WordOccurrence[capacity_];
}

void WordList::extend(const string & str){
    if(size_ >= capacity_){
        capacity_ *= 2;//double capacity
        WordOccurrence * temp = new WordOccurrence[capacity_];
        for (int i = 0; i < size_; i++){
            temp[i] = wordArray_[i];
        }
        std::swap(temp, wordArray_);
    }
    wordArray_[size_] = WordOccurrence(str);
    ++size_;
}

void WordList::addWord(const string & str){
    //scan wordArray for word
    bool matchFound = false;
    for(int i=0; i<size_; i++){
        WordOccurrence & wo = wordArray_[i];
        if(str.compare(wo.getWord()) == 0){
            matchFound = true;
            wo.increment();
            break;
        }
    }
    if(!matchFound){
        extend(str);   
    }
}

WordList::WordList(const WordList & other){
    size_ = other.size_;
    capacity_ = other.capacity_;
    delete [] wordArray_;
    wordArray_ = new WordOccurrence[capacity_];
    std::copy(other.wordArray_, other.wordArray_+size_, wordArray_);
}

WordList & WordList::operator =(WordList other){
    swap(*this, other);
    return *this;
}

void WordList::printList() const{
    std::sort(wordArray_, wordArray_ + size_);//don't forget to overload compare
    for (int i = 0; i < size_; i++){
        WordOccurrence wo = wordArray_[i];
        cout << wo.getWord() << ": " << wo.getNum() << endl; 
    }
}

void WordList::swap(WordList & first, WordList & second){
    std::swap(first.size_, second.size_);
    std::swap(first.capacity_, second.capacity_);
    std::swap(first.wordArray_, second.wordArray_);
}

WordList::~WordList(){
    delete [] wordArray_;
}