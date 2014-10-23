// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: mostly lifted from Proc C++
// 4/15/2014

#include <vector>
#include <list>
#include <stdexcept>
#include <string>

// using namespace std;
using std::string;
using std::invalid_argument;
using std::vector;
using std::list;
using std::pair;
using std::make_pair;

// Any Hash Class must provide two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
    // throws invalid_argument if numBuckets is illegal
    DefaultHash(size_t numBuckets = 101) throw (std::invalid_argument);
    size_t hash(const T& key) const;
    size_t numBuckets() const { return mNumBuckets; }
    //my code:
    //exchanges content, possibly resizing
    
    
protected:
    size_t mNumBuckets;
};

// Specialization for strings
template <>
class DefaultHash<string>{
public:
    // throws invalid_argument if numBuckets is illegal
    DefaultHash(size_t numBuckets = 101) throw (std::invalid_argument);
    size_t hash(const string& key) const;
    size_t numBuckets() const { return mNumBuckets; }
    
protected:
    size_t mNumBuckets;
};

template <typename Key, typename T, typename Compare = std::equal_to<Key>,
typename Hash = DefaultHash<Key>>
class hashmap{
    
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    
    // Constructors
    // throws invalid_argument if the hash object specifies an illegal
    // number of buckets.
    hashmap(const Compare& comp = Compare(),
            const Hash& hash = Hash()) throw(std::invalid_argument);
    
    // destructor, copy constructor, move constructor,
    // copy assignment operator and move assignment operator
    ~hashmap();
    hashmap(const hashmap<Key, T, Compare, Hash>& src);
    hashmap(hashmap<Key, T, Compare, Hash>&& src);        // C++11
    hashmap<Key, T, Compare, Hash>& operator=(const hashmap<
                                              Key, T, Compare, Hash>& rhs);
    hashmap<Key, T, Compare, Hash>& operator=(hashmap<
                                              Key, T, Compare, Hash>&& rhs);  // C++11
    
    // inserts the key/value pair x
    void insert(const value_type& x);
    
    // removes the element with key x, if it exists
    void erase(const key_type& x);
    
    // find returns a pointer to the element with key x.
    // Returns nullptr if no element with that key exists.
    value_type* find(const key_type& x);
    
    // operator[] finds the element with key x or inserts an
    // element with that key if none exists yet. Returns a reference to
    // the value corresponding to that key.
    T& operator[] (const key_type& x);
    
    //exchange content possible resizing
    void swap(hashmap<Key, T, Compare, Hash>& toSwap);
    //return load_factor=size/cap
    double load_factor();
    //increase size if nessesary and rearrange elements accordingly
    void rehash(size_t n);
    //accessor for finding out proper rehash size
    size_t currentNumBuckets();
    
protected:
    typename std::list<pair<const Key, T>>::iterator
    findElement(const key_type& x, size_t& bucket) const;
    
    typedef std::list<value_type> ListType;
    
    // In this first implementation, it would be easier to use a vector
    // instead of a pointer to a vector, which requires dynamic allocation.
    // However, a pointer to a vector is used so that, in the final
    // implementation, swap() can be implemented in constant time.
    std::vector<ListType>* mElems;
    size_t mSize;
    Compare mComp;
    Hash mHash;
};

// Throws invalid_argument if numBuckets is illegal
template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) throw (invalid_argument) {
    if (numBuckets <= 0)
        throw invalid_argument("numBuckets must be > 0");
        mNumBuckets = numBuckets;
        }

// Uses the division method for hashing.
// Treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
    size_t bytes = sizeof(key);
    size_t res = 0;
    for (size_t i = 0; i < bytes; ++i) {
        unsigned char b = *((unsigned char*)&key + i);
        res += b;
    }
    return res % mNumBuckets;
}

// Throws invalid_argument if numBuckets is illegal
DefaultHash<string>::DefaultHash(size_t numBuckets) throw (invalid_argument) {
    if (numBuckets <= 0) {
        throw invalid_argument("numBuckets must be > 0");
    }
    mNumBuckets = numBuckets;
}

// Uses the division method for hashing after summing the
// ASCII values of all the characters in key.
size_t DefaultHash<string>::hash(const string& key) const{
    size_t sum = 0;
    for (size_t i = 0; i < key.size(); i++) {
        sum += (unsigned char)key[i];
    }
    return sum % mNumBuckets;
}

// Construct mElems with the number of buckets.
template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>::hashmap(
                                        const Compare& comp, const Hash& hash) throw(invalid_argument) :
mSize(0), mComp(comp), mHash(hash) {
    if (mHash.numBuckets() <= 0)
        throw invalid_argument("Number of buckets must be positive");
    mElems = new std::vector<ListType>(mHash.numBuckets());
}

template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>::~hashmap() {
    delete mElems;
    mElems = nullptr;
    mSize = 0;
}

template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>::
hashmap(const hashmap< Key, T, Compare, Hash>& src) :
mSize(src.mSize), mComp(src.mComp), mHash(src.mHash) {
    // Don't need to bother checking if numBuckets is positive, because
    // we know src checked.
    
    // Use the vector copy constructor
    mElems = new std::vector<ListType>(*(src.mElems));
}

// C++11 move constructor
template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>::hashmap(hashmap<Key, T, Compare, Hash>&& src) {
    // move ownership
    mElems = src.mElems;
    src.mElems = nullptr;
    mSize = src.mSize;
    src.mSize = 0;
    mComp = src.mComp;
    mHash = src.mHash;
}


template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>& hashmap<Key, T, Compare, Hash>::operator=(
                                                                          const hashmap<Key, T, Compare, Hash>& rhs) {
    // check for self-assignment
    if (this != &rhs) {
        delete mElems;
        mSize = rhs.mSize;
        mComp = rhs.mComp;
        mHash = rhs.mHash;
        // Don't need to bother checking if numBuckets is positive, because
        // we know rhs checked.
        
        // Use the vector copy constructor
        mElems = new std::vector<ListType>(*(rhs.mElems));
    }
    return *this;
}

// C++11 move assignment operator
template <typename Key, typename T, typename Compare, typename Hash>
hashmap<Key, T, Compare, Hash>& hashmap<Key, T, Compare, Hash>::operator=(
                                                                          hashmap<Key, T, Compare, Hash>&& rhs) {
    // check for self-assignment
    if (this != &rhs) {
        delete mElems;
        
        // move ownership
        mElems = rhs.mElems;
        rhs.mElems = nullptr;
        mSize = rhs.mSize;
        rhs.mSize = 0;
        mComp = rhs.mComp;
        mHash = rhs.mHash;
    }
    return *this;
}

template <typename Key, typename T, typename Compare, typename Hash>
typename std::list<pair<const Key, T>>::iterator
hashmap<Key, T, Compare, Hash>::
findElement(const key_type& x, size_t& bucket) const {
    // hash the key to get the bucket
    bucket = mHash.hash(x);
    
    // Look for the key in the bucket
    for (auto it = (*mElems)[bucket].begin();
         it != (*mElems)[bucket].end(); ++it) {
	    if (mComp(it->first, x)) {
            return it;
	    }
    }
    return (*mElems)[bucket].end();
}

template <typename Key, typename T, typename Compare, typename Hash>
typename hashmap<Key, T, Compare, Hash>::value_type*
hashmap<Key, T, Compare, Hash>::find(const key_type& x) {
    size_t bucket;
    // Use the findElement() helper
    auto it = findElement(x, bucket);
    if (it == (*mElems)[bucket].end()) {
        // we didn't find the element -- return nullptr
        return nullptr;
    }
    // We found the element. Return a pointer to it.
    return &(*it);
}

template <typename Key, typename T, typename Compare, typename Hash>
T& hashmap<Key, T, Compare, Hash>::operator[] (const key_type& x) {
    // Try to find the element. If it doesn't exist, add a new element.
    value_type* found = find(x);
    if (found == nullptr) {
        insert(make_pair(x, T()));
        found = find(x);
    }
    return found->second;
}

template <typename Key, typename T, typename Compare, typename Hash>
void hashmap<Key, T, Compare, Hash>::insert(const value_type& x) {
    size_t bucket;
    // Try to find the element
    auto it = findElement(x.first, bucket);
    
    if (it != (*mElems)[bucket].end()) {
        // The element already exists
        return;
    } else {
        // We didn't find the element, so insert a new one.
        mSize++;
        (*mElems)[bucket].insert((*mElems)[bucket].end(), x);
    }
}

template <typename Key, typename T, typename Compare, typename Hash>
void hashmap<Key, T, Compare, Hash>::erase(const key_type& x) {
    size_t bucket;
    
    // First, try to find the element
    auto it = findElement(x, bucket);
    
    if (it != (*mElems)[bucket].end()) {
        // The element exists -- erase it
        (*mElems)[bucket].erase(it);
        mSize--;
    }
}
