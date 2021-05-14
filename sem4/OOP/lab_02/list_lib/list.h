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
    List() noexcept;
    explicit List(List<T> &list);
    List(List<T> &&list) noexcept;
    List(T *const array, const int &size);
    List(initializer_list<T> nodes);
    template<typename V>
    List(V itBegin, V itEnd);
    virtual ~List() = default;

    bool isEmpty() const override;
    void clear();
    void swap(List<T> &other) noexcept;

    void pushFront(const T &data);
    void pushFront(const List<T> &list);

    void pushBack(const T &data);
    void pushBack(const List<T> &list);

    T popFront();
    T popBack();

    void insert(ListIterator<T> &it, const T &data);
    void insert(ListIterator<T> &it, const List<T> &list);

    template<typename V>
    void insert(ListIterator<T> &it, const V &first, const V &last);
    template<typename V>
    void insert(ConstListIterator<T> &it, const V &first, const V &last);

    T remove(const ListIterator<T> &it);
    void reverse();

    List<T> &operator= (List<T> &&list) noexcept;
    List<T> &operator= (const List<T> &list);

    List<T> &operator+= (const List<T> &list);
    List<T> &operator+= (const T &data);

    List<T> &operator+ (const List<T> &list);
    List<T> &operator+ (const T &data);

    bool operator== (const List<T> &list) const;
    bool operator!= (const List<T> &list) const;

    ListIterator<T> begin();
    ConstListIterator<T> begin() const;
    ConstListIterator<T> cbegin() const;

    ListIterator<T> end();
    ConstListIterator<T> end() const;
    ConstListIterator<T> cend() const;

private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    size_t size;

    void setTail(shared_ptr<Node<T>> newTail);
    void setHead(shared_ptr<Node<T>> newHead);

    shared_ptr<Node<T>> reverseOrder(shared_ptr<Node<T>> temp);
};

#include "list.hpp"

#endif // LIST_LIB_LIST_H