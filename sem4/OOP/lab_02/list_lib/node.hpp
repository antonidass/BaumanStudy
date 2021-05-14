#ifndef LIST_LIB_NODE_HPP
#define LIST_LIB_NODE_HPP


template <typename T>
Node<T>::Node() {
    this->next = nullptr;
}


template <typename T>
Node<T>::Node(const T &data) {
    this->next = nullptr;
    this->data = data;
}


template <typename T>
Node<T>::Node(shared_ptr<Node<T>> &node) {
    this->next = node->next;
    this->data = node->data;
}


template <typename T>
void Node<T>::setNext(const shared_ptr<Node<T>> &node) {
    this->next = node;
}


template <typename T>
void Node<T>::setNext(const Node<T> &node) {
    shared_ptr<Node<T>> nodePtr(node);
    this->next = nodePtr;
}


template <typename T>
void Node<T>::setNextNull() {
    this->next = nullptr;
}


template <typename T>
T &Node<T>::getData() {
    return this->data;
}


template <typename T>
const T& Node<T>::getData() const {
    return this->data;
}


template <typename T>
shared_ptr<Node<T>> Node<T>::getNext() {
    return this->next;
}


#endif //LIST_LIB_NODE_HPP
