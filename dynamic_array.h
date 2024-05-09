#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

template<typename T>
class dynamic_array {
private:
    T *array;
    int capacity;
    int size;

public:
    dynamic_array();
    ~dynamic_array();
    T& operator[](int index);
    const T& operator[](int index) const; // Const version of operator[]
    int getSize() const;
    void append(T element);

private:
    void resize(int new_capacity);
};

template<typename T>
dynamic_array<T>::dynamic_array() {
    capacity = 2;
    size = 0;
    array = new T[capacity];
}

template<typename T>
dynamic_array<T>::~dynamic_array() {
    delete[] array;
}

template<typename T>
T& dynamic_array<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template<typename T>
const T& dynamic_array<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return array[index];
}

template<typename T>
int dynamic_array<T>::getSize() const {
    return size;
}

template<typename T>
void dynamic_array<T>::append(T element) {
    if (size == capacity) {
        resize(2 * capacity);
    }
    array[size++] = element;
}

template<type