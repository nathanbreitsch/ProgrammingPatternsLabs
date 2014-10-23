#ifndef WORD_OCCURRENCE_H
#define WORD_OCCURRENCE_H

#include <string>
using std::string;
    
class WordOccurrence {
public:
    WordOccurrence(const string word, int num=1);
    WordOccurrence();
    WordOccurrence(const WordOccurrence &);//copy constructor
    WordOccurrence& operator=(const WordOccurrence);//assignment operator
    bool matchWord(const string &) const; // returns true if word matches stored
    void increment(); // increments number of occurences
    string getWord() const; 
    int getNum(void) const;
    bool operator <(const WordOccurrence &) const;
    friend void swap(WordOccurrence &, WordOccurrence &);
    

private:
    string word_;
    int num_;
};

#endif