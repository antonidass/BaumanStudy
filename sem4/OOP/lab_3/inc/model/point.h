#ifndef DOT_H
#define DOT_H

#include "../object/object.h"

class Point {
public:
    Point() = default;
    Point(const double x, const double y, const double z);
    Point(const Point &point) = default;
    Point(const Point &&point) noexcept;
    ~Point() = default;

    void move (const double dx, const double dy, const double dz);
    void scale (const double kx, const double ky, const double kz);
    void rotate (const double ox, const double oy, const double oz);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double const &x);
    void setY(double const &y);
    void setZ(double const &z);

    virtual void accept(Visitor *visitor);

    bool operator == (const Point &point) const noexcept;
    bool operator != (const Point &point) const noexcept;
    bool isEqual (const Point &point) const noexcept;
    bool isNotEqual (const Point &point) const noexcept;

    Point &operator = (const Point &point) = default;
    Point &operator = (Point &&point) noexcept;
    Point operator + (const Point &point);
    Point operator - (const Point &point);

    Point withCenter(const Point &center);

private:
    void rotateX(const double &ox);
    void rotateY(const double &oy);
    void rotateZ(const double &oz);

    double _x;
    double _y;
    double _z;
};

#endif
