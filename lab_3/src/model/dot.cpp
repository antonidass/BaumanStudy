#include "../../inc/model/dot.h"
#include <cmath>

double to_radians(const double &angle)
{
    return angle * (M_PI / 180);
}

Dot::Dot(const double x, const double y, const double z)
{
    set_x(x);
    set_y(y);
    set_z(z);
}

Dot::Dot(const Dot &&dot) noexcept
{
    set_x(dot._x);
    set_y(dot._y);
    set_z(dot._z);

    dot.~Dot();
}

Dot &Dot::operator = (Dot &&dot) noexcept
{
    set_x(dot._x);
    set_y(dot._y);
    set_z(dot._z);

    dot.~Dot();

    return *this;
}

double Dot::get_x() const
{
    return _x;
}

double Dot::get_y() const
{
    return _y;
}

double Dot::get_z() const
{
    return _z;
}

void Dot::set_x(const double &x)
{
    _x = x;
}

void Dot::set_y(const double &y)
{
    _y = y;
}

void Dot::set_z(const double &z)
{
    _z = z;
}

bool Dot::operator == (const Dot &dot) const noexcept
{
    return (dot._x == _x) && (dot._y == _y) && (dot._z == _z);
}

bool Dot::is_equal(const Dot &dot) const noexcept
{
    return *this == dot;
}

bool Dot::operator != (const Dot &dot) const noexcept
{
    return !(*this == dot);
}

bool Dot::is_not_equal(const Dot &dot) const noexcept {
    return !(*this == dot);
}

Dot Dot::operator + (const Dot &dot)
{
    Dot d{*this};

    d.set_x(d._x + dot._x);
    d.set_y(d._y + dot._y);
    d.set_z(d._z + dot._z);

    return d;
}

Dot Dot::operator - (const Dot &dot)
{
    Dot d{*this};

    d.set_x(d._x - dot._x);
    d.set_y(d._y - dot._y);
    d.set_z(d._z - dot._z);

    return d;
}

void Dot::move(const double dx, const double dy, const double dz)
{
    set_x(_x + dx);
    set_y(_y + dy);
    set_z(_y + dz);
}

void Dot::scale(const double kx, const double ky, const double kz)
{
    set_x(_x * kx);
    set_y(_y * ky);
    set_z(_z * kz);
}

void Dot::rotate(const double ox, const double oy, const double oz)
{
    rotate_x(ox);
    rotate_y(oy);
    rotate_z(oz);
}

void Dot::rotate_x(const double &ox)
{
    const double cos_rotate = cos(to_radians(ox));
    const double sin_rotate = sin(to_radians(ox));

    const double tmp = _y;

    set_y(_y * cos_rotate + _z * sin_rotate);
    set_z(_z * cos_rotate - tmp * sin_rotate);
}

void Dot::rotate_y(const double &oy)
{
    const double cos_rotate = cos(to_radians(oy));
    const double sin_rotate = sin(to_radians(oy));

    const double tmp = _x;

    set_x(_x * cos_rotate + _z * sin_rotate);
    set_z(_z * cos_rotate - tmp * sin_rotate);
}

void Dot::rotate_z(const double &oz)
{
    const double cos_rotate = cos(to_radians(oz));
    const double sin_rotate = sin(to_radians(oz));

    const double tmp = _x;

    set_x(_x * cos_rotate + _y * sin_rotate);
    set_y(_y * cos_rotate - tmp * sin_rotate);
}

Dot Dot::with_center(const Dot &center)
{
    return (*this) + center;
}
