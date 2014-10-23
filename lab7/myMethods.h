#include "hashmap.h"
//exchange the contents of the hashmaps
template <typename Key, typename T, typename Compare, typename Hash>
void hashmap<Key, T, Compare, Hash>::
swap(hashmap<Key, T, Compare, Hash>& toSwap){
    //swap sizes
    std::swap(mSize, toSwap.mSize);
    //swap bucket counts (by swaping hashes)
    std::swap(mHash, toSwap.mHash);
    //swap contents
    std::swap(mElems, toSwap.mElems);
    
}
//return load_factor=size/cap
template <typename Key, typename T, typename Compare, typename Hash>
double hashmap<Key, T, Compare, Hash>::
load_factor(){
    return (double) mHash.numBuckets() / mSize;
}
//increase size if nessesary and rearrange elements accordingly
template <typename Key, typename T, typename Compare, typename Hash>
void hashmap<Key, T, Compare, Hash>::
rehash(size_t n){
    if(n <= mHash.numBuckets()){return;}//no need to shrink
    //use copy and swap idiom, but for hashmaps
    hashmap<Key, T, Compare, Hash> temp
    = *new hashmap<Key, T, Compare, Hash>(Compare(), Hash(n));
    for (auto& hashList : *mElems){
        for (const auto& kvPair : hashList){
            temp.insert(kvPair);
        }
    }
    swap(temp);
}

template <typename Key, typename T, typename Compare, typename Hash>
size_t hashmap<Key, T, Compare, Hash>::currentNumBuckets(){
    return mHash.numBuckets();
}