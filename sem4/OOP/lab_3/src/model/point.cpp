#include "../../inc/model/point.h"
#include <cmath>

double to_radians(const double &angle) {
    return angle * (M_PI / 180);
}

Point::Point(const double x, const double y, const double z) {
    setX(x);
    setY(y);
    setZ(z);
}

Point::Point(const Point &&point) noexcept {
    setX(point._x);
    setY(point._y);
    setZ(point._z);

    point.~Point();
}

Point &Point::operator = (Point &&point) noexcept {
    setX(point._x);
    setY(point._y);
    setZ(point._z);

    point.~Point();

    return *this;
}


void Point::accept(Visitor *vis)
{
    vis->visit(*this);
}


double Point::getX() const {
    return _x;
}

double Point::getY() const {
    return _y;
}

double Point::getZ() const {
    return _z;
}

void Point::setX(const double &x) {
    _x = x;
}

void Point::setY(const double &y) {
    _y = y;
}

void Point::setZ(const double &z) {
    _z = z;
}

bool Point::operator == (const Point &point) const noexcept {
    return (point._x == _x) && (point._y == _y) && (point._z == _z);
}

bool Point::isEqual(const Point &point) const noexcept {
    return *this == point;
}

bool Point::operator != (const Point &point) const noexcept {
    return !(*this == point);
}

bool Point::isNotEqual(const Point &point) const noexcept {
    return !(*this == point);
}

Point Point::operator + (const Point &point) {
    Point d{*this};

    d.setX(d._x + point._x);
    d.setY(d._y + point._y);
    d.setZ(d._z + point._z);

    return d;
}

Point Point::operator - (const Point &point) {
    Point d{*this};

    d.setX(d._x - point._x);
    d.setY(d._y - point._y);
    d.setZ(d._z - point._z);

    return d;
}

void Point::move(const double dx, const double dy, const double dz) {
    setX(_x + dx);
    setY(_y + dy);
    setZ(_y + dz);
}

void Point::scale(const double kx, const double ky, const double kz) {
    setX(_x * kx);
    setY(_y * ky);
    setZ(_z * kz);
}

void Point::rotate(const double ox, const double oy, const double oz) {
    rotateX(ox);
    rotateY(oy);
    rotateZ(oz);
}

void Point::rotateX(const double &ox) {
    const double cos_rotate = cos(to_radians(ox));
    const double sin_rotate = sin(to_radians(ox));

    const double tmp = _y;

    setY(_y * cos_rotate + _z * sin_rotate);
    setZ(_z * cos_rotate - tmp * sin_rotate);
}

void Point::rotateY(const double &oy) {
    const double cos_rotate = cos(to_radians(oy));
    const double sin_rotate = sin(to_radians(oy));

    const double tmp = _x;

    setX(_x * cos_rotate + _z * sin_rotate);
    setZ(_z * cos_rotate - tmp * sin_rotate);
}

void Point::rotateZ(const double &oz) {
    const double cos_rotate = cos(to_radians(oz));
    const double sin_rotate = sin(to_radians(oz));

    const double tmp = _x;

    setX(_x * cos_rotate + _y * sin_rotate);
    setY(_y * cos_rotate - tmp * sin_rotate);
}

Point Point::withCenter(const Point &center) {
    return (*this) + center;
}
