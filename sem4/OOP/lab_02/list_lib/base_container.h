#ifndef LIST_LIB_BASE_CONTAINER_H
#define LIST_LIB_BASE_CONTAINER_H

class BaseContainer {
public:
    virtual bool isEmpty() const = 0;
    virtual ~BaseContainer() = default;

protected:
    size_t size;
};

#endif //LIST_LIB_BASE_CONTAINER_H
