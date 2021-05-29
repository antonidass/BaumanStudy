#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator.h"
#include <QDebug>

template <typename T>
Iterator<T>::Iterator(const Iterator<T> &iterator) {
    this->ptr = iterator.ptr;
    this->currentIndex = iterator.currentIndex;
    this->vectorSize = iterator.vectorSize;
}

template <typename T>
Iterator<T>::Iterator(const Vector<T> &vector) {
    this->currentIndex = 0;
    this->vectorSize = vector.getSize();
    this->ptr = vector.value;
}

template <typename T>
T &Iterator<T>::operator*() {
    return *getCurrent();
}

template <typename T>
const T &Iterator<T>::operator*() const {
    return getCurrent();
}

template <typename T>
T *Iterator<T>::operator->() {
    return getCurrent();
}

template <typename T>
const T *Iterator<T>::operator->() const {
    return getCurrent();
}

template <typename T>
Iterator<T>::operator bool() const {
    return currentIndex >= vectorSize || !vectorSize ? false : true;
}

template <typename T>
Iterator<T> &Iterator<T>::operator+=(size_t number) {
    currentIndex += number;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(size_t number) const {
    Iterator<T> iterator(*this);
    iterator += number;
    return iterator;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++() {
    this->currentIndex++;

    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    ++(*this);

    return *this;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T> &iterator) const {
    return this->currentIndex == iterator.currentIndex;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T> &iterator) const {
    return this->currentIndex != iterator.currentIndex;
}

template <typename T>
T *Iterator<T>::getCurrent() const {
    return this->ptr.lock().get() + currentIndex;
}

#endif
