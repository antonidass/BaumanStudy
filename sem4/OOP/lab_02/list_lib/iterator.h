#ifndef LIST_LIB_ITERATOR_H
#define LIST_LIB_ITERATOR_H

#include <iterator>
#include "node.h"

template <typename T>
class BaseIterator : iterator<input_iterator_tag, T> {
public:
    BaseIterator();
    BaseIterator(const BaseIterator<T> &baseIt);
    BaseIterator(const shared_ptr<Node<T>> node);
    virtual ~BaseIterator() = default;

    BaseIterator<T> &operator=(const BaseIterator<T> &baseIt);

    BaseIterator<T> &next();
    BaseIterator<T> &operator++();
    BaseIterator<T> operator++(int);

    bool isOutOfBounds() const;

    bool operator==(const BaseIterator<T> &baseIt) const;
    bool operator!=(const BaseIterator<T> &baseIt) const;

protected:
    weak_ptr<Node<T>> ptr;
};


template <typename T>
class ListIterator : public BaseIterator<T> {
public:
    ListIterator();
    ListIterator(const ListIterator<T> &iterator);
    ListIterator(const shared_ptr<Node<T>> node);

    T &getCur();
    const T &getCur() const;

    T &getNext();
    const T &getNext() const;

    explicit operator bool() const;

    T *operator->();
    const T *operator->() const;

    T &operator*();
    const T &operator*() const;

    ListIterator<T> &operator+=(const int &size);
    ListIterator<T> operator+(const int &size) const;
    ListIterator<T> &operator=(const ListIterator<T> &it);
};


template <typename T>
class ConstListIterator : public BaseIterator<T> {
public:
    ConstListIterator();
    ConstListIterator(const ConstListIterator<T> &it);
    ConstListIterator(const shared_ptr<Node<T>> node);

    const T &getNext() const;
    const T &getCur() const;
    explicit operator bool() const;
    const T *operator->() const;
    const T &operator*() const;

    ConstListIterator<T> &operator=(const ConstListIterator<T> &it);
    ConstListIterator<T> &operator+= (const int &size);
    ConstListIterator<T> operator+ (const int &size) const;
};

#include "iterator.hpp"

#endif //LIST_LIB_ITERATOR_H
