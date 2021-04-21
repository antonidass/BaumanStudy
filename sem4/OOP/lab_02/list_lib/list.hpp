#ifndef LIST_LIB_LIST_HPP
#define LIST_LIB_LIST_HPP


template <typename T>
List<T>::List() {
    this->size = 0;
    this->setHead(nullptr);
    this->setTail(nullptr);
}


template <typename T>
List<T>::List(List<T> &&list) {
    this->size = list.size;
    this->setHead(list.head);
    this->setTail(list.tail);
}


template <typename T>
List<T>::List(List<T> &list) : List() {
    for (Node<T> node: list) {
        this->pushBack(node.getData());
    }
}


template <typename T>
List<T>::List(T *const array, const int &size) : List() {
    if (!array) {
        throw pointerException(__FUNCTION__);
    }

    if (size <= 0) {
        throw sizeException(__FUNCTION__);
    }

    for (int i = 0; i < size; i++) {
        this->pushBack(*(array + i));
    }
}


template <typename T>
List<T>::List(initializer_list<T> nodes) : List() {
    for (const Node<T> &node: nodes) {
        this->pushBack(node.getData());
    }
}


template <typename T>
template <typename V>
List<T>::List(V itBegin, V itEnd) : List() {
    for (auto it = itBegin; it != itEnd; ++it) {
        this->pushBack(*it);
    }
}


template <typename T>
bool List<T>::isEmpty() const {
    return this->head == nullptr;
}


template <typename T>
void List<T>::clear() {
    while (this->head) {
        this->popFront();
    }
}


template <typename T>
void List<T>::swap(List<T> &other) {
    shared_ptr<Node<T>> tempHead = other.getHead();
    shared_ptr<Node<T>> tempTail = other.getTail();

    other.setHead(this->head);
    other.setTail(this->tail);

    this->setHead(tempHead);
    this->setTail(tempTail);
}


template <typename T>
T List<T>::popFront() {
    if (!this->head) {
        throw emptyListException(__FUNCTION__ );
    }

    T data = this->head->getData();

    if (this->size == 1) {
        this->setHead(nullptr);
        this->setTail(nullptr);
    }
    else {
        this->head = this->head->getNext();
    }

    this->size--;

    return data;
}

template <typename T>
T List<T>::popBack() {
    if (this->isEmpty()) {
        throw emptyListException(__FUNCTION__ );
    }

    T data = this->tail->getData();

    if (this->size == 1) {
        this->setHead(nullptr);
        this->setTail(nullptr);
    }
    else {
        shared_ptr<Node<T>> penultimate = this->head;

        while (penultimate->getNext() != this->tail) {
            penultimate = penultimate->getNext();
        }

        this->tail = penultimate;
        this->tail->setNextNull();
    }

    this->size--;
    return data;
}


template <typename T>
void List<T>::pushBack(const List<T> &list) {
    for (int i = 0; i < list.size; i++) {
        this->pushBack(*(list.cbegin() + i));
    }
}


template <typename T>
void List<T>::pushBack(const T &data) {
    shared_ptr<Node<T>> node = make_shared<Node<T>>(data);

    if (!node) {
        throw memoryException(__FUNCTION__);
    }

    if (!this->size) {
        this->head = node;
    }
    else {
        this->tail->setNext(node);
    }

    this->tail = node;
    this->size++;
}


template <typename T>
void List<T>::pushFront(const List<T> &list) {
    for (int i = list.size - 1; i > -1; i--) {
        this->pushFront(*(list.cbegin() + i));
    }
}


template <typename T>
void List<T>::pushFront(const T &data) {
    shared_ptr<Node<T>> node = make_shared<Node<T>>(data);

    if (!node) {
        throw memoryException(__FUNCTION__);
    }

    node->setNext(this->head);

    this->head = node;

    if (!this->size) {
        this->tail = node;
    }

    this->size++;
}


template <typename T>
void List<T>::insert(ListIterator<T> &iterator, const T &data) {
    if (iterator.isOutOfBounds()) {
        throw iteratorException(__FUNCTION__);
    }

    if (iterator == this->begin()) {
        this->pushFront(data);
    }
    else if (iterator == this->end()) {
        this->pushBack(data);
    }
    else {
        std::shared_ptr<Node<T>> temp_node = make_shared<Node<T>>(data);

        if (!temp_node) {
            throw memoryException(__FUNCTION__ );
        }

        ListIterator<T> tempIt = this->begin();

        while (tempIt + 1 != iterator) {
            tempIt++;
        }

        shared_ptr<Node<T>> nextNode = iterator.getPtr().lock();
        tempIt.getPtr().lock()->setNext(temp_node);
        temp_node->setNext(nextNode);
        this->size++;
    }
}


template <typename T>
void List<T>::insert(ListIterator<T> &iterator, const List<T> &list) {
    if (iterator.isOutOfBounds()) {
        throw iteratorException(__FUNCTION__);
    }

    for (int i = 0; i < list.size; i++) {
        insert(iterator, (*(list.cbegin() + i)));
    }
}


template <typename T>
void List<T>::remove(const T& value)
{
    if (this->isEmpty()) {
        throw emptyListException(__FUNCTION__);
    }

    if (this->head->getData() == value) {
        this->popFront();
    }
    else {
        ListIterator<T> it = this->begin();
        while (it + 1 != this->end() && *(it + 1) != value) {
            it++;
        }

        if (it + 1 != this->end()) {
            shared_ptr<Node<T>> curNode = it.getPtr().lock();
            curNode->setNext(curNode->getNext()->getNext());
            this->size--;
        }
    }
}


template <typename T>
shared_ptr<Node<T>> List<T>::reverseOrder(shared_ptr<Node<T>> temp) {
    if (!temp) {
        return nullptr;
    }

    if (!temp->getNext()) {
        return temp;
    }

    shared_ptr<Node<T>> rev_head = reverseOrder(temp->getNext());
    shared_ptr<Node<T>> node = rev_head;

    while (node->getNext()) {
        node = node->getNext();
    }

    node->setNext(temp);
    temp->setNext(nullptr);

    return rev_head;
}


template <typename T>
void List<T>::reverse() {
    shared_ptr<Node<T>> tempTail = this->head;
    this->head = reverseOrder(this->head);
    this->tail = tempTail;
}


template <typename T>
bool List<T>::operator== (const List<T> &list) const {
    auto lIt = this->cbegin();
    auto rIt = list.cbegin();

    while (lIt != this->cend() && rIt != list.cend()) {
        if (*lIt != *rIt) {
            return false;
        }
        ++lIt;
        ++rIt;
    }

    return this->size == list.size;
}


template <typename T>
bool List<T>::operator!= (const List<T> &list) const {
    return !(*this == list);
}


template <typename T>
List<T> &List<T>::operator= (const List<T> &list) {
    this->clear();

    this->size = 0;
    this->setHead(nullptr);
    this->setTail(nullptr);

    pushBack(list);
    return *this;
}


template <typename T>
List<T> &List<T>::operator= (const List<T> &&list) {
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
}


template <typename T>
List<T> &List<T>::operator+= (const List<T> &list) {
    this->pushBack(list);
    return *this;
}


template <typename T>
List<T> &List<T>::operator+= (const T &data) {
    this->pushBack(data);
    return *this;
}


template<typename V>
ostream &operator<< (ostream &os, const List<V> &list) {
    for (auto it = list.cbegin(); it != list.cend(); it++) {
        os << (*it) << " ";
    }

    return os;
}


template <typename T>
ListIterator<T> List<T>::begin() {
    ListIterator<T> it(this->head);
    return it;
}


template <typename T>
ConstListIterator<T> List<T>::cbegin() const {
    ConstListIterator<T> it(this->head);
    return it;
}


template <typename T>
ListIterator<T> List<T>::end() {
    ListIterator<T> it(this->tail);
    return ++it;
}


template <typename T>
ConstListIterator<T> List<T>::cend() const {
    ConstListIterator<T> it(this->tail);
    return ++it;
}


template <typename T>
shared_ptr<Node<T>> List<T>::getHead() {
    return this->head;
}


template <typename T>
shared_ptr<Node<T>> List<T>::getTail() {
    return this->tail;
}


template <typename T>
void List<T>::setTail(shared_ptr<Node<T>> newTail) {
    this->tail = newTail;
}


template <typename T>
void List<T>::setHead(shared_ptr<Node<T>> newHead) {
    this->head = newHead;
}

#endif //LIST_LIB_LIST_HPP