#include "point.h"

#define PI 3.1415
#include <QDebug>

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(const double x, const double y, const double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Point &point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

Point& Point::operator=(const Point& point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;

    return *this;
}

Point::Point(const Point &&point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    point.~Point();
}

Point& Point::operator=(Point &&point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
    point.~Point();

    return *this;
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

double Point::getZ() const {
    return this->z;
}

void Point::setX(double const &x) {
    this->x = x;
}

void Point::setY(double const &y) {
    this->y = y;
}

void Point::setZ(double const &z) {
    this->z = z;
}

void Point::move(const double dx, const double dy, const double dz) {
    this->x += dx;
    this->y += dy;
    this->z += dz;
}

void Point::scale(const double kx, const double ky, const double kz) {
    this->x *= kx;
    this->y *= ky;
    this->z *= kz;
}

void Point::rotate(const double ox, const double oy, const double oz) {
    this->rotateX(ox);
    this->rotateY(oy);
    this->rotateZ(oz);
}

void Point::rotateX(const double &ox) {
    const double temp_y = this->y;
    this->y = y + cos(ox * PI / 180) + z * sin(ox * PI / 180);
    this->z = -temp_y * sin(ox * PI / 180) + z * cos(ox * PI / 180);
}

void Point::rotateY(const double &oy) {
    const double temp_x = this->x;
    this->x = x * cos(oy * PI / 180) + z * sin(oy * PI / 180);
    this->z = -temp_x * sin(oy * PI / 180) + z * cos(oy * PI / 180);
}

void Point::rotateZ(const double &oz) {
    const double temp_x = this->x;
    this->x = x * cos(oz * PI / 180) + y * sin(oz * PI / 180);
    this->y = -temp_x * sin(oz * PI / 180) + y * cos(oz * PI / 180);
}
