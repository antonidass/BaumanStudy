#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include "iterator.h"

class baseVector {
public:
    virtual size_t getSize() const = 0;
    virtual bool   isEmpty() const = 0;
    virtual ~baseVector() = default;

protected:
    size_t size;
};



template <typename T>
class Vector : public baseVector {
public:
    friend class Iterator<T>;

    Vector();
    Vector(const T *array, size_t size);
    Vector(T elem, size_t size);

    virtual ~Vector() = default;

    virtual size_t getSize() const;
    virtual bool isEmpty() const;

    T at(size_t index) const;

    Vector<T> &pushBack(const T &elem);
    Vector<T> &operator += (const T &elem);

    Iterator<T> begin();
    const Iterator<T> begin() const;

    Iterator<T> end();
    const Iterator<T> end() const;

protected:
    void allocateNew(size_t size);

private:
    shared_ptr<T[]> value;
    size_t memoryAllocated;
};

#endif
