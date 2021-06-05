#ifndef VISITOR_H
#define VISITOR_H

#include <memory>

class Figure;
class Composite;
class Point;
class Camera;

class Visitor {
public:
    Visitor() = default;
    ~Visitor() = default;

    virtual void visit(std::shared_ptr<Composite> obj) = 0;
    virtual void visit(std::shared_ptr<Figure> model) = 0;
    virtual void visit(std::shared_ptr<Camera> camera) = 0;
    virtual void visit(Point& point) = 0;
};

#endif
