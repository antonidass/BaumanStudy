#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>
#include <memory>
using namespace std;

template <typename T>
class Vector;

template <typename T>
class Iterator : public iterator<input_iterator_tag, T> {
public:
    Iterator(const Iterator<T> &iterator);
    Iterator(const Vector<T> &vector);

    T &operator*();
    const T &operator*() const;

    T *operator->();
    const T *operator->() const;

    operator bool() const;

    Iterator<T> &operator+=(size_t number);
    Iterator<T> operator+(size_t number) const;

    Iterator<T> &operator++();
    Iterator<T> operator++(int);

    bool operator==(const Iterator<T> &iterator) const;
    bool operator!=(const Iterator<T> &iterator) const;

private:
    weak_ptr<T[]> ptr;
    T *getCurrent() const;
    size_t currentIndex;
    size_t vectorSize;
};


#endif
