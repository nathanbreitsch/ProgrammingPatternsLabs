
#include "WordOccurrence.h"

//copy constructor
WordOccurrence::WordOccurrence(const string word, int num): word_(word), num_(num) {}
WordOccurrence::WordOccurrence():word_(""), num_(1){}

bool WordOccurrence::matchWord(const string& other) const{
    return word_.compare(other) == 0;//use string compare
}

string WordOccurrence::getWord() const{
    return word_;
}

int WordOccurrence::getNum() const{
    return num_;
}

void WordOccurrence::increment(){
    ++ num_;
}

bool WordOccurrence::operator <(const WordOccurrence & other)const{
    return (num_ > other.getNum());   
}

WordOccurrence::WordOccurrence(const WordOccurrence & other){
    num_ = other.getNum();
    word_ = other.getWord();
}


void swap(WordOccurrence & first, WordOccurrence & second){
    std::swap(first.num_, second.num_);
    first.word_ = second.getWord();
}

WordOccurrence & WordOccurrence::operator =(WordOccurrence other){
    swap(*this, other);
    return *this;
}