#ifndef LIST_LIB_LIST_H
#define LIST_LIB_LIST_H

#include <memory>
#include <initializer_list>

#include "base_container.h"
#include "node.h"
#include "iterator.h"
#include "exceptions.h"


template <typename T>
class List : public BaseContainer {
public:
    List();
    List(List<T> &list);
    List(List<T> &&list);
    List(T *const array, const int &size);
    List(initializer_list<T> nodes);
    template<typename V>
    List(V itBegin, V itEnd);



    bool isEmpty() const override;
    void clear();
    void swap(List<T> &other);

    void pushFront(const T &data);
    void pushFront(const List<T> &list);

    void pushBack(const T &data);
    void pushBack(const List<T> &list);

    T popFront();
    T popBack();

    void insert(ListIterator<T> &iterator, const T &data);
    void insert(ListIterator<T> &iterator, const List<T> &list);

    void remove(const T& value);
    void reverse();


    List<T> &operator = (const List<T> &&list);
    List<T> &operator = (const List<T> &list);

    List<T> &operator += (const List<T> &list);
    List<T> &operator += (const T &data);

    bool operator == (const List<T> &list) const;
    bool operator != (const List<T> &list) const;

    ListIterator<T> begin();
    ConstListIterator<T> cbegin() const;

    ListIterator<T> end();
    ConstListIterator<T> cend() const;

    shared_ptr<Node<T>> getHead();
    shared_ptr<Node<T>> getTail();

    void setTail(shared_ptr<Node<T>> newTail);
    void setHead(shared_ptr<Node<T>> newHead);

private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    size_t size;

    shared_ptr<Node<T>> reverseOrder(shared_ptr<Node<T>> temp);
};

#include "list.hpp"

#endif //LIST_LIB_LIST_H
