#ifndef LIST_LIB_NODE_H
#define LIST_LIB_NODE_H

#include <memory>
using namespace std;


template <typename T>
class Node {
public:
    Node();
    explicit Node(const T &data);
    explicit Node(shared_ptr<Node<T>> &node);
    ~Node() = default;

    void setNext(const shared_ptr<Node<T>> &node);
    void setNext(const Node<T> &node);
    void setNextNull();

    T &getData();
    const T& getData() const;
    shared_ptr<Node<T>> getNext();

private:
    T data;
    shared_ptr<Node<T>> next;
};

#include "node.hpp"

#endif //LIST_LIB_NODE_H