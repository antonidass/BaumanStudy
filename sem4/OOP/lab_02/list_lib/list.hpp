#ifndef LIST_LIB_LIST_HPP
#define LIST_LIB_LIST_HPP


template <typename T>
List<T>::List() noexcept {
    this->size = 0;
    this->setHead(nullptr);
    this->setTail(nullptr);
}


template <typename T>
List<T>::List(List<T> &&list) noexcept {
    this->size = list.size;
    this->setHead(list.head);
    this->setTail(list.tail);
}


template <typename T>
List<T>::List(List<T> &list) : List() {
    auto it = list.begin();
    for (; it != list.end() + 1; it++) {
        this->pushBack(*it);
    }
}


template <typename T>
List<T>::List(T *const array, const int &size) : List() {
    if (!array) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw pointerException(__FUNCTION__, ctime(&time));
    }

    if (size <= 0) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw sizeException(__FUNCTION__, ctime(&time));
    }

    for (int i = 0; i < size; i++) {
        this->pushBack(*(array + i));
    }
}


template <typename T>
List<T>::List(initializer_list<T> nodes) : List() {
    for (const T &data: nodes) {
        this->pushBack(data);
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
void List<T>::swap(List<T> &other) noexcept {
    shared_ptr<Node<T>> tempHead = other.head;
    shared_ptr<Node<T>> tempTail = other.tail;

    other.setHead(this->head);
    other.setTail(this->tail);

    this->setHead(tempHead);
    this->setTail(tempTail);
}


template <typename T>
T List<T>::popFront() {
    if (!this->head) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw emptyListException(__FUNCTION__ , ctime(&time));
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
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw emptyListException(__FUNCTION__ , ctime(&time));
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
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw memoryException(__FUNCTION__, ctime(&time));
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
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw memoryException(__FUNCTION__, ctime(&time));
    }

    node->setNext(this->head);

    this->head = node;

    if (!this->size) {
        this->tail = node;
    }

    this->size++;
}


template <typename T>
void List<T>::insert(ListIterator<T> &it, const T &data) {
    shared_ptr<Node<T>> curNode = this->head;
    shared_ptr<Node<T>> tmp = nullptr;
    ListIterator<T> cur = this->begin();

    if (this->head == nullptr && cur == it) {
        shared_ptr<Node<T>> newNode = make_shared<Node<T>>(data);

        if (!newNode) {
            auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            throw memoryException(__FUNCTION__, ctime(&time));
        }
        this->head = newNode;
        this->tail = newNode;
        return;
    }

    for (; curNode && cur != it; tmp = curNode, curNode = curNode->getNext(), cur.next()) { ; }

    if (curNode == nullptr) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    shared_ptr<Node<T>> newNode = make_shared<Node<T>>(data);

    if (!newNode) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw memoryException(__FUNCTION__, ctime(&time));
    }

    if (curNode == this->head) {
        newNode->setNext(this->head);
        this->head = newNode;
    } else {
        newNode->setNext(tmp->getNext());
        tmp->setNext(newNode);
    }
}


template <typename T>
void List<T>::insert(ListIterator<T> &it, const List<T> &list) {
    if (it.isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    for (int i = 0; i < list.size; i++) {
        insert(it, (*(list.cbegin() + i)));
    }
}


template <typename T>
template<typename V>
void List<T>::insert(ListIterator<T> &it, const V &first, const V &last) {
    if (it.isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    for (auto cur = first; cur != last; cur++) {
        insert(it, *cur);
    }
}


template <typename T>
template<typename V>
void List<T>::insert(ConstListIterator<T> &it, const V &first, const V &last) {
    if (it.isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    for (auto cur = first; cur != last; cur++) {
        insert(it, *cur);
    }
}



template <typename T>
T List<T>::remove(const ListIterator<T> &it) {
    if (it.isOutOfBounds()) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    if (!this->size) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw emptyListException(__FUNCTION__ , ctime(&time));
    }

    shared_ptr<Node<T>> curNode = this->head;
    shared_ptr<Node<T>> tmp = nullptr;
    ListIterator<T> cur = this->begin();

    for (; curNode && cur != it; tmp = curNode, curNode = curNode->getNext(), cur.next()) { ; }

    if (curNode == nullptr) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw iteratorException(__FUNCTION__, ctime(&time));
    }

    T data = it.getCur();

    if (curNode->getNext() == nullptr) {
        this->tail = tmp;
    }

    if (curNode == this->head) {
        this->head = this->head->getNext();
    } else {
        tmp->setNext(curNode->getNext());
    }

    this->size--;

    return data;
}


template <typename T>
shared_ptr<Node<T>> List<T>::reverseOrder(shared_ptr<Node<T>> temp) {
    if (!temp) {
        auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        throw emptyListException(__FUNCTION__, ctime(&time));
    }

    if (!temp->getNext()) {
        return temp;
    }

    shared_ptr<Node<T>> revHead = reverseOrder(temp->getNext());
    shared_ptr<Node<T>> node = revHead;

    while (node->getNext()) {
        node = node->getNext();
    }

    node->setNext(temp);
    temp->setNext(nullptr);

    return revHead;
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
List<T> &List<T>::operator+ (const List<T> &list) {
    this->pushBack(list);
    return *this;
}


template <typename T>
List<T> &List<T>::operator+ (const T &data) {
    this->pushBack(data);
    return *this;
}


template <typename T>
List<T> &List<T>::operator= (List<T> &&list) noexcept {
    this->size = list.size;
    this->setHead(list.head);
    this->setTail(list.tail);
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
ostream &operator<< (ostream &os, List<V> &list) {
    ListIterator<V> it = list.begin();
    for (; !it.isOutOfBounds(); it.next()) {
        os << it.getCur() << " ";
    }
    os << endl;

    return os;
}


template <typename T>
ConstListIterator<T> List<T>::begin() const {
    return cbegin();
}

template <typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>(head);
}

template <typename T>
ConstListIterator<T> List<T>::cbegin() const {
    return ConstListIterator<T>(head);
}


template <typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>(tail);
}


template <typename T>
ConstListIterator<T> List<T>::cend() const {
    return ConstListIterator<T>(tail);
}

template <typename T>
ConstListIterator<T> List<T>::end() const {
    return cend();
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