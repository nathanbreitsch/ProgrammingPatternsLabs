// tests hashmap container implementation
// Mikhail Nesterenko, lifted from Pro C++
// 4/20/2014

#include "hashmap.h"
#include <iostream>
// using namespace std;

using std::cout; using std::endl;
using std::make_pair;

int main(){
   hashmap<string, int> myHash;
   myHash.insert(make_pair("KeyOne", 100));
   myHash.insert(make_pair("KeyTwo", 200));
   myHash.insert(make_pair("KeyThree", 300));
   myHash.insert(make_pair("KeyFour", 400));

  for (auto& kvpair : myHash){
    cout << kvpair.first << kvpair.second << endl;
  }

}
