#include "../../inc/visitor/transform_visitor.h"
#include <math.h>


TransformVisitor::TransformVisitor(const double x, const double y, const double z) : p1(x), p2(y), p3(z) {}

MoveVisitor::MoveVisitor(const double x, const double y, const double z) : TransformVisitor(x, y, z) {}


void MoveVisitor::visit(std::shared_ptr<Composite> obj) {
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void MoveVisitor::visit(std::shared_ptr<Figure> model) {
    model->accept(this);
}

void MoveVisitor::visit(std::shared_ptr<Camera> camera) {
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    x += p1;
    y += p2;
    z += p3;

    camera->setX(x);
    camera->setY(y);
    camera->setZ(z);
}

void MoveVisitor::visit(Point &point) {
    point.move(p1, p2, p3);
}



ScaleVisitor::ScaleVisitor(const double x, const double y, const double z) : TransformVisitor(x, y, z)
{}

void ScaleVisitor::visit(std::shared_ptr<Composite> obj)
{
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void ScaleVisitor::visit(std::shared_ptr<Figure> model)
{
    model->accept(this);
}

void ScaleVisitor::visit(std::shared_ptr<Camera> camera)
{
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    x *= p1;
    y *= p2;
    z *= p3;

    camera->setX(x);
    camera->setY(y);
    camera->setZ(z);
}

void ScaleVisitor::visit(Point &point)
{
    double x = point.getX();
    double y = point.getY();
    double z = point.getZ();

    x *= p1;
    y *= p2;
    z *= p3;

    point.setX(x);
    point.setY(y);
    point.setZ(z);
}



RotateVisitor::RotateVisitor(const double x, const double y, const double z) : TransformVisitor(x, y, z)
{}

void RotateVisitor::visit(std::shared_ptr<Composite> obj)
{
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void RotateVisitor::visit(std::shared_ptr<Figure> model)
{
    model->accept(this);
}

void RotateVisitor::visit(std::shared_ptr<Camera> camera)
{
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    Point p = Point(x, y, z);
    p.rotate(p1, p2, p3);

    camera->setX(p.getX());
    camera->setY(p.getY());
    camera->setZ(p.getZ());
}

void RotateVisitor::visit(Point &point)
{
    point.rotate(p1, p2, p3);
}
