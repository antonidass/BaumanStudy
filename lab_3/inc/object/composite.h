#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "object.h"
#include "../visitor/visitor.h"
#include "../scene/scene.h"

class Composite : public Object
{
friend std::vector<std::shared_ptr<Object>> Scene::get_models();

public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object> &element);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vector);

    bool is_visible()   override;
    bool is_composite() override;

    bool add(const std::shared_ptr<Object> &element) override;
    bool remove(const Iterator &iter) override;

    virtual void transform(const Dot &move, const Dot &scale, const Dot &rotate) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

    Iterator begin() override;
    Iterator end()   override;

protected:
    std::vector<std::shared_ptr<Object>> _elements;
};

#endif
