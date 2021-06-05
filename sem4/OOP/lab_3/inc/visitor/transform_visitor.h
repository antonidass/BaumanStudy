#ifndef LAB_03_TRANSFORM_VISITOR_H
#define LAB_03_TRANSFORM_VISITOR_H

#include "visitor.h"
#include "memory"

#include "../model/point.h"
#include "../object/composite.h"
#include "../object/figure.h"
#include "../object/camera.h"


class TransformVisitor : public Visitor {
public:
    TransformVisitor(const double x, const double y, const double z);

protected:
    double p1;
    double p2;
    double p3;
};

class MoveVisitor : public TransformVisitor {
public:
    MoveVisitor(const double x, const double y, const double z);

    virtual void visit(std::shared_ptr<Composite> obj);
    virtual void visit(std::shared_ptr<Figure> model);
    virtual void visit(std::shared_ptr<Camera> camera);
    virtual void visit(Point& point);
};


class ScaleVisitor: public TransformVisitor {
public:
    ScaleVisitor(const double x, const double y, const double z);

    virtual void visit(std::shared_ptr<Composite> obj);
    virtual void visit(std::shared_ptr<Figure> model);
    virtual void visit(std::shared_ptr<Camera> camera);
    virtual void visit(Point& point);
};


class RotateVisitor: public TransformVisitor {
public:
    RotateVisitor(const double x, const double y, const double z);

    virtual void visit(std::shared_ptr<Composite> obj);
    virtual void visit(std::shared_ptr<Figure> model) ;
    virtual void visit(std::shared_ptr<Camera> camera) ;
    virtual void visit(Point& point) override;
};

#endif //LAB_03_TRANSFORM_VISITOR_H
