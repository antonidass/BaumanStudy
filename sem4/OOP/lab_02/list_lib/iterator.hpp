#ifndef LIST_LIB_ITERATOR_HPP
#define LIST_LIB_ITERATOR_HPP

#include "exceptions.h"



template <typename T>
BaseIterator<T>::BaseIterator() {
    this->ptr.lock() = nullptr;
}

template <typename T>
BaseIterator<T>::BaseIterator(const BaseIterator<T> &it) : ptr(it.ptr){}

template <typename T>
BaseIterator<T>::BaseIterator(const shared_ptr<Node<T>> node) : ptr(node) {}

template <typename T>
BaseIterator<T> &BaseIterator<T>::operator= (const BaseIterator<T> &it) {
    if (this != &it) {
        this->ptr = it.ptr;
    }
    return *this;
}


template <typename T>
BaseIterator<T>& BaseIterator<T>::next() {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    this->ptr = this->ptr.lock()->getNext();
    return *this;
}

template <typename T>
BaseIterator<T> BaseIterator<T>::operator++ (int) {
    BaseIterator<T> newIt(*this);
    this->operator++();
    return newIt;
}

template <typename T>
BaseIterator<T> &BaseIterator<T>::operator++ () {
    this->next();
    return *this;
}

template <typename T>
bool BaseIterator<T>::isOutOfBounds() const {
    return this->ptr.lock() == nullptr;
}

template <typename T>
bool BaseIterator<T>::operator!= (const BaseIterator<T> &it) const {
    return this->ptr.lock() != it.ptr.lock();
}

template <typename T>
bool BaseIterator<T>::operator== (const BaseIterator<T> &it) const {
    return this->ptr.lock() == it.ptr.lock();
}



template <typename T>
ListIterator<T>::ListIterator() : BaseIterator<T>() {}

template <typename T>
ListIterator<T>::ListIterator(const shared_ptr<Node<T>> node) : BaseIterator<T>(node) {}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> &it) : BaseIterator<T>(it) {}


template<typename T>
T &ListIterator<T>::getCur() {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}


template<typename T>
const T &ListIterator<T>::getCur() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}


template <typename T>
T &ListIterator<T>::getNext() {
    if (this->isOutOfBounds() || this->ptr.lock()->getNext() == nullptr) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getNext()->getData();
}


template <typename T>
const T &ListIterator<T>::getNext() const {
    if (this->isOutOfBounds() || this->ptr.lock()->getNext() == nullptr) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getNext()->getData();
}

template <typename T>
T* ListIterator<T>::operator->() {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return &this->ptr.lock()->getData();
}

template <typename T>
const T* ListIterator<T>::operator->() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return &this->ptr.lock()->getData();
}

template <typename T>
const T& ListIterator<T>::operator*() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}

template <typename T>
T& ListIterator<T>::operator*() {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator+= (const int &size) {
    if (size < 0) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw sizeException(__FUNCTION__, ctime(&time));
    }

    for (int i = 0; i < size; i++) {
        if (this->ptr.lock() == nullptr) {
            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            throw pointerException(__FUNCTION__, ctime(&time));
        }
        this->next();
    }

    return *this;
}


template <typename T>
ListIterator<T> ListIterator<T>::operator+ (const int &size) const {
    if (size < 0) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw sizeException(__FUNCTION__, ctime(&time));
    }

    ListIterator<T> newIt(*this);
    newIt += size;
    return newIt;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator= (const ListIterator<T> &it) {
    if (this != &it) {
        this->ptr = it.ptr;
    }
    return *this;
}

template <typename T>
ListIterator<T>::operator bool() const {
    return this->ptr.lock() != nullptr;
}



template <typename T>
ConstListIterator<T>::ConstListIterator() : BaseIterator<T>() {}

template <typename T>
ConstListIterator<T>::ConstListIterator(const ConstListIterator<T> &it) : BaseIterator<T>(it){}

template <typename T>
ConstListIterator<T>::ConstListIterator(const std::shared_ptr<Node<T>> node) : BaseIterator<T>(node){}


template <typename T>
const T &ConstListIterator<T>::getNext() const {
    if (this->isOutOfBounds() || this->ptr.lock()->getNext() == nullptr) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getNext()->getData();
}

template<typename T>
const T &ConstListIterator<T>::getCur() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}


template <typename T>
const T* ConstListIterator<T>::operator->() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return &this->ptr.lock()->getData();
}


template <typename T>
const T& ConstListIterator<T>::operator*() const {
    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    return this->ptr.lock()->getData();
}


template <typename T>
ConstListIterator<T>::operator bool() const {
    return this->ptr.lock() != nullptr;
}

template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator= (const ConstListIterator<T> &it) {
    if (this != &it) {
        this->ptr = it.ptr;
    }
    return *this;
}


template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator+= (const int &size) {
    if (size < 0) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw sizeException(__FUNCTION__, ctime(&time));
    }

    for (int i = 0; i < size; i++) {
        if (this->ptr.lock() == nullptr) {
            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            throw pointerException(__FUNCTION__, ctime(&time));
        }
        this->next();
    }

    return *this;
}


template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator+ (const int &size) const {
    if (size < 0) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw sizeException(__FUNCTION__, ctime(&time));
    }

    if (this->isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    ConstListIterator<T> newIt(*this);
    newIt += size;
    return newIt;
}


#endif //LIST_LIB_ITERATOR_HPP
