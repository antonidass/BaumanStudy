#ifndef LIST_LIB_ITERATOR_HPP
#define LIST_LIB_ITERATOR_HPP

#include "exceptions.h"


template <typename T>
ListIterator<T>::ListIterator() {
    this->ptr.reset();
}


template <typename T>
ListIterator<T>::ListIterator(const shared_ptr<Node<T>> &node) {
    this->ptr = node;
}


template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> &it) {
    this->ptr = it.ptr.lock();
}


template <typename T>
void ListIterator<T>::next() {
    this->ptr = this->ptr.lock()->getNext();
}


template <typename T>
bool ListIterator<T>::isOutOfBounds() const {
    return this->ptr.lock() == nullptr;
}


template <typename T>
ListIterator<T>::operator bool() const {
    return this->ptr.lock() != nullptr;
}


template<typename T>
weak_ptr<Node<T>> ListIterator<T>::getPtr() {
    return this->ptr;
}


template <typename T>
T* ListIterator<T>::operator->() {
    return this->ptr;
}


template <typename T>
const T* ListIterator<T>::operator->() const {
    return this->ptr;
}


template <typename T>
const T& ListIterator<T>::operator*() const {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    return this->ptr.lock()->getData();
}


template <typename T>
T& ListIterator<T>::operator*() {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    return this->ptr.lock()->getData();
}


template <typename T>
ListIterator<T> ListIterator<T>::operator++ (int) {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    ListIterator<T> newIt(*this);
    this->next();
    return newIt;
}


template <typename T>
ListIterator<T> &ListIterator<T>::operator++ () {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    this->ptr = this->ptr.lock()->getNext();
    return *this;
}


template <typename T>
bool ListIterator<T>::operator!= (const ListIterator<T> &it) const {
    return this->ptr.lock() != it.ptr.lock();
}


template <typename T>
bool ListIterator<T>::operator== (const ListIterator<T> &it) const {
    return this->ptr.lock() == it.ptr.lock();
}


template <typename T>
ListIterator<T> &ListIterator<T>::operator+= (const int &size) {
    if (size < 0) {
        throw sizeException(__FUNCTION__);
    }

    for (int i = 0; i < size; i++) {
        if (this->getPtr().lock() == nullptr) {
            throw pointerException(__FUNCTION__);
        }
        this->next();
    }

    return *this;
}


template <typename T>
ListIterator<T> ListIterator<T>::operator+ (const int &size) const {
    if (size < 0) {
        throw sizeException(__FUNCTION__);
    }

    ListIterator<T> newIt(*this);
    newIt += size;
    return newIt;
}


template <typename T>
ListIterator<T> ListIterator<T>::operator= (const ListIterator<T> &it) {
    this->ptr = it.ptr.lock();
    return *this;
}




template <typename T>
ConstListIterator<T>::ConstListIterator() {
    this->ptr = nullptr;
}


template <typename T>
ConstListIterator<T>::ConstListIterator(const ConstListIterator<T> &it) {
    this->ptr = it.ptr.lock();
}


template <typename T>
ConstListIterator<T>::ConstListIterator(const std::shared_ptr<Node<T>> &node) {
    this->ptr = node;
}


template <typename T>
void ConstListIterator<T>::next() {
    this->ptr = this->ptr.lock()->getNext();
}


template <typename T>
bool ConstListIterator<T>::isOutOfBounds() const {
    return this->ptr.lock() == nullptr;
}


template <typename T>
const T* ConstListIterator<T>::operator->() const {
    return this->ptr.lock().get();
}


template <typename T>
weak_ptr<Node<T>> ConstListIterator<T>::getPtr() {
    return this->ptr;
}


template <typename T>
const T& ConstListIterator<T>::operator*() const {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    return this->ptr.lock()->getData();
}


template <typename T>
ConstListIterator<T>::operator bool() const {
    return this->ptr.lock() != nullptr;
}


template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator++ () {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    this->next();
    return *this;
}


template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator++ (int) {
    if (this->isOutOfBounds()) {
        throw iteratorException(__FUNCTION__ );
    }

    ConstListIterator<T> newIt(*this);
    this->next();
    return newIt;
}


template <typename T>
bool ConstListIterator<T>::operator!= (const ConstListIterator<T> &it) const {
    return this->ptr.lock() != it.ptr.lock();
}


template <typename T>
bool ConstListIterator<T>::operator== (const ConstListIterator<T> &it) const {
    return this->ptr.lock() == it.ptr.lock();
}


template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator+= (const int &size) {
    if (size < 0) {
        throw sizeException(__FUNCTION__);
    }

    for (int i = 0; i < size; i++) {
        if (this->getPtr().lock() == nullptr) {
            throw pointerException(__FUNCTION__);
        }
        this->next();
    }

    return *this;
}


template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator= (const ListIterator<T> &it) {
    this->ptr = it.ptr.lock();
    return *this;
}


template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator+ (const int &size) const {
    if (size < 0) {
        throw sizeException(__FUNCTION__);
    }

    ConstListIterator<T> newIt(*this);
    newIt += size;
    return newIt;
}


#endif //LIST_LIB_ITERATOR_HPP
