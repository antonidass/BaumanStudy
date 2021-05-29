#ifndef VECTOR_HPP
#define VECTOR_HPP

    #include <QDebug>
#include "vector.h"
#include "iterator.h"

template <typename T>
Vector<T>::Vector() {
    this->size = 0;
    this->allocateNew(100);
}

template <typename T>
Vector<T>::Vector(const T *array, size_t _size) {
    this->allocateNew(_size * 2);

    for (int i = 0; i < _size; i++) {
        this->pushBack(*(array + i));
    }
}

template <typename T>
Vector<T>::Vector(T elem, size_t _size) {
    this->allocateNew(_size * 2);

    for (int i = 0; i < _size; i++) {
        this->pushBack(elem);
    }
}

template <typename T>
size_t Vector<T>::getSize() const {
    return this->size;
}

template <typename T>
bool Vector<T>::isEmpty() const {
    return this->size == 0 ? true : false;
}

template <typename T>
T Vector<T>::at(size_t index) const {
    return this->value[index];
}

template <typename T>
Vector<T> &Vector<T>::pushBack(const T &elem) {
    if (this->size >= memoryAllocated) {
        allocateNew(size * 2);
    }

    this->value[this->size++] = elem;
}

template <typename T>
Vector<T> &Vector<T>::operator += (const T &elem) {
    this->pushBack(elem);
}


template <typename T>
Iterator<T> Vector<T>::begin() {
    Iterator<T> iterator(*this);
    return iterator;
}

template <typename T>
Iterator<T> Vector<T>::end() {
    Iterator<T> iterator(*this);
    return iterator + this->size;
}

template <typename T>
const Iterator<T> Vector<T>::begin() const {
    const Iterator<T> iterator(*this);
    return iterator;
}

template <typename T>
const Iterator<T> Vector<T>::end() const {
    const Iterator<T> iterator(*this);
    return iterator + this->size;
}

template <typename T>
void Vector<T>::allocateNew(size_t new_size) {

    try {
        this->value.reset(new T[new_size]);
    } catch (std::bad_alloc &exception) {
        exception.what();
    }

    this->memoryAllocated = new_size;
}

#endif
