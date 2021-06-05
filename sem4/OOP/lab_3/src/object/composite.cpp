#include "../../inc/object/composite.h"

Composite::Composite(std::shared_ptr<Object> &el) {
    _elements.push_back(el);
}

Composite::Composite(const std::vector<std::shared_ptr<Object>> &vector) {
    _elements = vector;
}

bool Composite::add(const std::shared_ptr<Object> &el) {
    _elements.push_back(el);
    return true;
}

bool Composite::remove(const Iterator &it) {
    _elements.erase(it);
    return true;
}

bool Composite::isComposite() {
    return true;
}

Iterator Composite::begin() {
    return _elements.begin();
}

Iterator Composite::end() {
    return _elements.end();
}

void Composite::accept(Visitor *visitor) {
    for (auto element : _elements) {
        element->accept(visitor);
    }
}

bool Composite::isVisible() {
    return false;
}
