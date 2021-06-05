#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "object.h"
#include "../scene/scene.h"

class Composite : public Object {
friend std::vector<std::shared_ptr<Object>> Scene::getFigures();


public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object> &el);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vector);

    bool isComposite() override;
    virtual bool isVisible();

    bool add(const std::shared_ptr<Object> &el) override;
    bool remove(const Iterator &it) override;

    void accept(Visitor *visitor) override;

    Iterator begin() override;
    Iterator end() override;

private:
    std::vector<std::shared_ptr<Object>> _elements;
};

#endif
