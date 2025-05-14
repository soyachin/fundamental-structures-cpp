#include "../include/Hash.h"
#include <forward_list>
#include <iterator>

template<typename TK, typename TV>
Hash<TK,TV>::Hash(int _capacity){
    array = new forward_list<Bucket>[_capacity];
    capacity = _capacity;
    size = 0;
}

template<typename TK, typename TV>
void Hash<TK,TV>::insert(const TK& key, const TV& value) { // Worst case (O(n*k))
   if (fill_factor() >= MAX_FILL_FACTOR) rehash();

   size_t h = get_hash_code(key); // hash code  
   int index = h % capacity;

   auto& chain = array[index];

   for (auto& bucket : chain) {
       if (bucket.key == key) {
           bucket.value = value; // Behaves like an unordered_map because it updates the            value
           return;
       }
   }
    
   chain.emplace_front(key, value, h);
   ++size;

}

template<typename TK, typename TV>
bool Hash<TK,TV>::remove(const TK& key){
    int h = get_hash_code(key);
    int index = h % capacity;
    auto& chain = array[index];
    for (auto& bucket : chain) { // O(1) , Worst O(n)
        if (bucket.key == key ){
            chain.remove(bucket);
            --size;
            return true;
        }
    }

    return false;
    
}

template<typename TK, typename TV>
TV* Hash<TK,TV>::get(const TK& key) const{
    int h = get_hash_code(key);
    int index = h % capacity;
    auto& chain = array[index];

    for (auto& bucket : chain) { // O(1) // Worst O(N)
        if (bucket.key == key ){
            return bucket;
        }
    }

    return TV(0);

}

template<typename TK, typename TV>
void Hash<TK,TV>::rehash(){
    int new_cap = capacity*2;
    forward_list<Bucket>* new_hash = forward_list<Bucket>(new_cap);

    for (int i = 0; i < capacity; ++i){ // O(n*k)
        for (const auto& bucket : array[i]){
            size_t new_index = bucket.hashcode % new_cap;
            new_hash[new_index].emplace_front(bucket.key, bucket.value, buckey.hashcode);
        }
    }

    array = move(new_hash);
    capacity = new_cap;

}

template<typename TK, typename TV>
int Hash<TK,TV>::bucket_size(const TK& key) {
    int h = get_hash_code(key);
    int index = h % capacity;
    auto& chain = array[index];

    return distance(chain.begin(), chain.end()); // o(n)

}







