//
// Created by hojas on 12/05/25.
//

#ifndef ARRAY_H
#define ARRAY_H
#include <cstddef>

template <typename T>
class ArrayIterator {
    private:
      T** ptr;
    public:
        explicit ArrayIterator(T** point = nullptr) : ptr(point) {}

        T& operator*() const { return **ptr; }
        T* operator->() const { return *ptr; }

        ArrayIterator& operator++() { ++ptr; return *this; }    // Prefix ++
        ArrayIterator& operator--() { --ptr; return *this; }    // Prefix --

        bool operator==(const ArrayIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ArrayIterator& other) const { return ptr != other.ptr; }
        bool operator<(const ArrayIterator& other) const { return ptr < other.ptr; }
        bool operator>(const ArrayIterator& other) const { return ptr > other.ptr; }
        bool operator<=(const ArrayIterator& other) const { return ptr <= other.ptr; }
        bool operator>=(const ArrayIterator& other) const { return ptr >= other.ptr; }

        ArrayIterator operator+(size_t n) const { return ArrayIterator(ptr + n); }
        ArrayIterator operator-(size_t n) const { return ArrayIterator(ptr - n); }
        size_t operator-(const ArrayIterator& other) const { return ptr - other.ptr; }  // Distance
        ArrayIterator& operator+=(size_t n) { ptr += n; return *this; }
        ArrayIterator& operator-=(size_t n) { ptr -= n; return *this; }
        T& operator[](size_t n) const { return **(ptr + n); }

};

template <typename T>
class Array {
      T** data;
      size_t size;
      size_t capacity;
      typedef ArrayIterator<T> iterator;
    void resize(size_t new_capacity);
    public:
        iterator begin() { return iterator(data); }
        iterator end() { return iterator(data + size); }
        Array(size_t initial_capacity = 10);
        ~Array();
        void push_back(const T& value);
        void pop_back();
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        size_t get_size() const;
        size_t get_capacity() const;
        void clear();
};





#endif //ARRAY_H
