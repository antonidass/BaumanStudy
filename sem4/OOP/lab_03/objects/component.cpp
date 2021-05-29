#include "component.h"
#include "../visitor/visitor.h"



void CameraComponent::moveX(const double &dx) {
    this->currentPos.setX(this->currentPos.getX() + dx);
}

void CameraComponent::moveY(const double &dy) {
    this->currentPos.setY(this->currentPos.getY() + dy);
}

void CameraComponent::moveZ(const double &dz) {
    this->currentPos.setZ(this->currentPos.getZ() + dz);
}

CameraComponent::CameraComponent(const Point &pos) : currentPos(pos) {}

void CameraComponent::transform(const Point &new_pos, const Point &scale, const Point &turn) {
    this->moveX(new_pos.getX());
    this->moveY(new_pos.getY());
}

void CameraComponent::accept(shared_ptr<Visitor> visitor) {
    visitor->visit(*this);
}

Point CameraComponent::getPosition() { return currentPos; }



Composite::Composite(shared_ptr<Component> &component) {
    this->components.pushBack(component);
}

Composite::Composite(Vector<shared_ptr<Component>> vector) {
    this->components = vector;
}

bool Composite::add(const shared_ptr<Component> &component) {
    this->components.pushBack(component);
    return true;
}


Iterator<std::shared_ptr<Component>> Composite::begin() {
    return this->components.begin();
}

Iterator<std::shared_ptr<Component>> Composite::end() {
    return this->components.end();
}

bool Composite::isComposite() const {
    return true;
}

size_t Composite::size() const {
    return this->components.getSize();
}

void Composite::transform(const Point &move, const Point &scale, const Point &turn) {
    for (auto elem: components) {
        elem->transform(move, scale, turn);
    }
}

void Composite::accept(shared_ptr<Visitor> visitor) {
    for (auto obj: components) {
        obj->accept(visitor);
    }
}

Vector<shared_ptr<Component> > &Composite::getObjects() { return components; }




FigureComponent::FigureComponent() : figure(new Figure) {}

FigureComponent::FigureComponent(const shared_ptr<Figure> model) : figure(model) {}

FigureComponent::FigureComponent(const FigureComponent &modelComponent) {
    this->figure = modelComponent.getFigure();
}

std::unique_ptr<FigureComponent> FigureComponent::clone() {
    return std::unique_ptr<FigureComponent>(new FigureComponent(*this));
}

const shared_ptr<Figure> FigureComponent::getFigure() const { return figure; }

void FigureComponent::addPoint(const Point &point) {
    this->figure->addPoint(point);
}

void FigureComponent::addLink(const Link &link) {
    this->figure->addLink(link);
}

bool FigureComponent::isVisible() const {
    return true;
}

void FigureComponent::transform(const Point &move_coeff, const Point &scale_coeff, const Point &turn_coeff) {
    this->figure->transform(move_coeff, scale_coeff, turn_coeff);
}

void FigureComponent::accept(shared_ptr<Visitor> _visitor) {
    _visitor->visit(*this);
}


bool Component::add(const shared_ptr<Component> &) { return false; }

Iterator<shared_ptr<Component> > Component::begin() {}

Iterator<shared_ptr<Component> > Component::end()   {}

bool Component::isComposite() const { return false; }

bool Component::isVisible() const {
    return false;
}
