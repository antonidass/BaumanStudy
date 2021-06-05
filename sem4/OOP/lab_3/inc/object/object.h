#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

#include "../visitor/visitor.h"

class Visitor;
class Object;

using Iterator = std::vector<std::shared_ptr<Object>>::iterator;

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual bool isComposite() { return false; };
    virtual bool isVisible() = 0;

    virtual void accept(Visitor *visitor) = 0;

    virtual bool add(const std::shared_ptr<Object> &) { return false; };
    virtual bool remove(const Iterator &) { return false; };

    virtual Iterator begin() { return Iterator(); };
    virtual Iterator end() { return Iterator(); };
};
#endif
