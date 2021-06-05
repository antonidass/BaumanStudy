#include "../../inc/object/camera.h"


void Camera::moveX(const double &dx) {
    _pos.setX(_pos.getX() + dx);
}

void Camera::moveY(const double &dy) {
    _pos.setY(_pos.getY() + dy);
}

void Camera::moveZ(const double &dz) {
    _pos.setZ(_pos.getZ() + dz);
}

void Camera::accept(Visitor *visitor) {
    visitor->visit(std::shared_ptr<Camera>(this));
}

bool Camera::isComposite() {
    return false;
}

double Camera::getX() const
{
    return _pos.getX();
}

double Camera::getY() const
{
    return _pos.getY();
}

double Camera::getZ() const
{
    return _pos.getZ();
}


void Camera::setX(const double x)
{
    _pos.setX(x);
}

void Camera::setY(const double y)
{
    _pos.setY(y);
}



void Camera::setZ(const double z)
{
    _pos.setZ(z);
}

bool Camera::isVisible() {
    return false;
}
