#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

#include "../vector/iterator.hpp"
#include "../visitor/visitor.h"
#include "point.h"
#include "figure.h"
#include "link.h"


class Component {
public:
    Component() = default;
    virtual ~Component() = default;

    virtual bool add(const shared_ptr<Component> &);

    virtual Iterator<shared_ptr<Component>> begin();
    virtual Iterator<shared_ptr<Component>> end();

    virtual bool isComposite() const;
    virtual void accept(shared_ptr<Visitor> visitor) = 0;
    virtual void transform(const Point &move, const Point &scale, const Point &rotate) = 0;

    virtual bool isVisible() const;
};


class Composite : public Component {
public:
    Composite() = default;
    Composite(shared_ptr<Component> &component);
    Composite(Vector<shared_ptr<Component>> vector);

    size_t size() const;

    virtual bool add(const shared_ptr<Component> &component) override;

    virtual Iterator<shared_ptr<Component>> begin() override;
    virtual Iterator<shared_ptr<Component>> end() override;

    virtual bool isComposite() const override;
    virtual void transform(const Point &move, const Point &scale, const Point &rotate) override;
    virtual void accept(shared_ptr<Visitor> visitor) override;

    Vector<shared_ptr<Component>> &getObjects();

private:
    Vector<shared_ptr<Component>> components;
};


class CameraComponent : public Component {
public:
    CameraComponent() = default;
    CameraComponent(const Point &pos);
    ~CameraComponent() = default;

    virtual void transform(const Point &pos, const Point &rotate, const Point &scale) override;
    virtual void accept(shared_ptr<Visitor> visitor) override;
    Point getPosition();

    void moveX(const double &dx);
    void moveY(const double &dy);
    void moveZ(const double &dz);

private:
    Point currentPos;
};


class FigureComponent : public Component {
public:
    FigureComponent();
    FigureComponent(const shared_ptr<Figure> figure);
    FigureComponent(const FigureComponent &figureComp);
    ~FigureComponent() = default;

    unique_ptr<FigureComponent> clone();

    const shared_ptr<Figure> getFigure() const;
    void addPoint(const Point &point);
    void addLink (const Link &link);

    virtual bool isVisible() const override;

    virtual void transform(const Point &move, const Point &scale, const Point &rotate) override;
    virtual void accept(shared_ptr<Visitor> visitor) override;

private:
    shared_ptr<Figure> figure;
};


#endif
