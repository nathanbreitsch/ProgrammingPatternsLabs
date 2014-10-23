
#ifndef WORD_LIST_H
#define WORD_LIST_H

#include "WordOccurrence.h"


class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
    void addWord(const string &);
    void printList() const;
    WordList();
    ~WordList();
    WordList(const WordList &);
    WordList & operator =(WordList);
    void swap(WordList&, WordList&);
    
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
    int capacity_; //capacity of wordArray
    void extend(const string &);//add word that doesn't exist yet
};

#endif