#include "../include/Hash.h"

template<typename TK, typename TV>
Hash<TK,TV>::Hash(int _capacity){
    array = new forward_list<Bucket>[_capacity];
    capacity = _capacity;
    size = 0;
}

template<typename TK, typename TV>
void Hash<TK,TV>::insert(const TK& key, const TV& value) {
   if (fill_factor() > MAX_FILL_FACTOR) rehash();

   size_t h = get_hash_code(key); // hash code  
   int index = h % capacity;

   auto& chain = array[index];

   for (auto& bucket : chain) {
       if (bucket.key == key) {
           return;
       }
   }


}


