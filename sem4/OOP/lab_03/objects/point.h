#ifndef POINT_H
#define POINT_H

#include <math.h>

class Point {
public:
    Point();
    Point(const double x, const double y, const double z);

    Point(const Point &point);
    Point& operator=(const Point &point);

    Point(const Point &&point);
    Point& operator=(Point &&point);

    ~Point() = default;

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double const &x);
    void setY(double const &y);
    void setZ(double const &z);

    void move(const double dx, const double dy, const double dz);
    void scale(const double kx, const double ky, const double kz);
    void rotate(const double ox, const double oy, const double oz);

    void rotateX(const double &ox);
    void rotateY(const double &oy);
    void rotateZ(const double &oz);

private:
    double x, y, z;
};

#endif
