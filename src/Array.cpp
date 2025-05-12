//
// Created by hojas on 12/05/25.
//

#include <stdexcept>

#include "../include/Array.h"

template <typename T>
Array<T>::Array(size_t initial_capacity) : size(0), capacity(initial_capacity) {
    data = new T[capacity]();
}

template <typename T>
Array<T>::~Array() {
    clear();
    delete[] data;
}

template <typename T>
void Array<T>::push_back(const T& value) {
    if (size == capacity)
        resize(capacity * 2);

    data[size] = new T(value);
    size++;

}

template <typename T>
void Array<T>::pop_back() {
    if (size == 0)
        throw std::out_of_range("Array is empty");

    delete data[size - 1];
    data[size - 1] = nullptr; // Evitar dangling pointer
    --size;
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return *data[index];
}

template <typename T>
void Array<T>::clear() {
     while(size > 0)
        pop_back();
}

template <typename T>
size_t Array<T>::get_size() const {
    return size;
}

template <typename T>
size_t Array<T>::get_capacity() const {
    return capacity;
}

template <typename T>
void Array<T>::resize(size_t new_capacity){
  T** new_data = new T*[new_capacity];
  for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
  }

  delete[] data;
  data = new_data;
  capacity = new_capacity;
}

