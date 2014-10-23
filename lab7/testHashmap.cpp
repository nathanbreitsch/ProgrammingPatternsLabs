// demoes hashmap implementation
// Mikhail Nesterenko
// 4/15/2014

//#include "hashmap.h"
#include "myMethods.h"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
    hashmap<int, int> myHash;
    const size_t MIN_LOAD_FACTOR = 2;
    
    
    for(int i = 0; i < 200; ++i){
        myHash.insert(make_pair(i, (i*i*i + 6) % 32));
        cout << "size: " << i << endl << "load factor: " << myHash.load_factor() << endl;
        if(myHash.load_factor() < MIN_LOAD_FACTOR){
            myHash.rehash(2*myHash.currentNumBuckets());
        }
    }
    
    
    
}
