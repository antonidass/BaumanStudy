#ifndef FIGURE_H
#define FIGURE_H

#include "../vector/vector.hpp"
#include "../vector/iterator.hpp"
#include "link.h"
#include "point.h"

class Figure {
public:
    Figure() = default;
    Figure(Vector<Point> &points, Vector<Link> &links);
    ~Figure() = default;

    void addPoint(const Point &point);
    void addLink(const Link &link);
    const Vector<Point> &getPoints() const;
    const Vector<Link> &getLinks() const;
    void transform(const Point &move, const Point &scale, const Point &rotate);

private:
    Vector<Point> points;
    Vector<Link> links;
};

#endif
