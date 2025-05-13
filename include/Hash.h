#ifndef HASH_H
#define HASH_H

#include <cmath>
#include <forward_list>
#include <cstddef>
#include <functional>
#include <forward_list>

const float MAX_FILL_FACTOR = 0.7;

using namespace std;

// trata de imitar a std::unordered_map

template<typename TK, typename TV>
class Hash {
    struct Bucket {
        TK key;
        TV value;
        size_t hashcode; 
        
        explicit Bucket(TK k, TV v, size_t h) : key(k), value(v), hashcode(h) {}
        bool operator==(const TK& k) const {return k == key;}

    };

    forward_list<Bucket>* array; // pointer pq es un array 
    int size;
    int capacity;

    double fill_factor() {return static_cast<double>(size)/capacity;}
    size_t get_hash_code(const TK& key) const {return hash<TK>{}(key);}

    void rehash();


    public:
        explicit Hash(int _capacity = 10);
        void insert(const TK& key, const TV& value);
        TV* get(const TK& key) const;
        bool remove(const TK& key);
        int bucket_count() const {return capacity;}
        int getsize() const {return size;}
        int bucket_size(const TK& key);

        
};


#endif // HASH_H
