#ifndef LIST_LIB_ITERATOR_H
#define LIST_LIB_ITERATOR_H

#include <iterator>
#include "node.h"


template <typename T>
class BaseIterator : iterator<input_iterator_tag, T> {
public:
    virtual ~BaseIterator() = default;

protected:
    weak_ptr<Node<T>> ptr;
    virtual bool isOutOfBounds() const = 0;
    virtual weak_ptr<Node<T>> getPtr() = 0;
};


template <typename T>
class ListIterator : BaseIterator<T> {
public:
    ListIterator();
    ListIterator(const ListIterator<T> &iterator);
    ListIterator(const shared_ptr<Node<T>> &node);

    virtual void next();
    bool isOutOfBounds() const override;
    weak_ptr<Node<T>> getPtr() override;

    operator bool() const;

    T* operator-> ();
    const T* operator-> () const;

    const T& operator* () const;
    T& operator* ();

    ListIterator<T> &operator++ ();
    ListIterator<T> operator++ (int);

    bool operator!= (const ListIterator<T> &it) const;
    bool operator== (const ListIterator<T> &it) const;

    ListIterator<T> &operator+= (const int &size);
    ListIterator<T> operator+ (const int &size) const;
    ListIterator<T> operator= (const ListIterator<T> &it);
};


template <typename T>
class ConstListIterator : BaseIterator<T> {
public:
    ConstListIterator();
    ConstListIterator(const ConstListIterator<T> &it);
    ConstListIterator(const shared_ptr<Node<T>> &node);

    virtual void next();
    virtual bool isOutOfBounds() const override;
    weak_ptr<Node<T>> getPtr() override;

    operator bool() const;

    const T *operator->() const;
    const T &operator*() const;

    ConstListIterator<T> &operator++ ();
    ConstListIterator<T> operator++ (int);

    bool operator!= (const ConstListIterator<T> &it) const;
    bool operator== (const ConstListIterator<T> &it) const;

    ConstListIterator<T> &operator+= (const int &size);
    ConstListIterator<T> operator+ (const int &size) const;
    ConstListIterator<T> operator= (const ListIterator<T> &it);
};

#include "iterator.hpp"

#endif //LIST_LIB_ITERATOR_H
