#include "figure.h"

Figure::Figure(Vector<Point> &_points, Vector<Link> &_links) : points(_points), links(_links) {}

void Figure::addPoint(const Point &point) {
    this->points.pushBack(point);
}

void Figure::addLink(const Link &link) {
    this->links.pushBack(link);
}

const Vector<Point> &Figure::getPoints() const {
    return this->points;
}

const Vector<Link> &Figure::getLinks() const {
    return this->links;
}

void Figure::transform(const Point &_move, const Point &_scale, const Point &_turn) {
    for (auto &pt: points) {
        pt.move(_move.getX(), _move.getY(), _move.getZ());
        pt.scale(_scale.getX(), _scale.getY(), _scale.getZ());
        pt.rotate(_turn.getX(), _turn.getY(), _turn.getZ());
    }
}
