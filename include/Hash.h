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

    void rehash() {
        int new_cap = capacity*2;
        forward_list<Bucket>* new_hash = forward_list<Bucket>(new_cap);

        for (int i = 0; i < capacity; ++i){ // O(n*k)
            for (const auto& bucket : array[i]){
                size_t new_index = bucket.hashcode % new_cap;
                new_hash[new_index].emplace_front(bucket.key, bucket.value, bucket.hashcode);
            }
        }

        array = move(new_hash);
        capacity = new_cap;

    }

    public:
        explicit Hash(int _capacity = 10){
            array = new forward_list<Bucket>[_capacity];
            capacity = _capacity;
            size = 0;
        }


        void insert(const TK& key, const TV& value){
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


        TV* get(const TK& key) const {
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


        bool remove(const TK& key) {
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
        int bucket_count() const {return capacity;}

        int getsize() const {return size;}

        int bucket_size(const TK& key){
            int h = get_hash_code(key);
            int index = h % capacity;
            auto& chain = array[index];

            return distance(chain.begin(), chain.end()); // o(n)
        }

        
};


#endif // HASH_H
