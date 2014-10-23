#include "WordOccurrence.h"
#include "WordList.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
using std::cout;
using std::endl;

int main(int argc, char* argv[]){
  
    if(argc != 2){
        cout << "usage: ./wordcount <filename>" << endl;
        return 1;
    }

    char* filename = argv[1];
    WordList * wl = new WordList();
    std::ifstream file;
    file.open(filename);
    string nextWord = "";
    char nextChar;
    while((nextChar = file.get()) && !file.eof()){
        if(isalnum(nextChar)){
            nextWord += nextChar;
        }
        else if(nextWord.length() > 0){
            wl->addWord(nextWord);
            nextWord = "";
        }
        
        
    }
    wl->printList();
    return 0;
    
}