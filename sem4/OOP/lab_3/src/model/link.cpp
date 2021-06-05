#include "../../inc/model/link.h"

Link::Link(const std::size_t &dot1, const std::size_t &dot2) {
    setFirstPoint(dot1);
    setSecondPoint(dot2);
}

std::size_t Link::getFirstPoint() const {
    return point1;
}

std::size_t Link::getSecondPoint() const {
    return point2;
}

void Link::setFirstPoint(const size_t &firstDot) {
    point1 = firstDot;
}

void Link::setSecondPoint(const size_t &secondDot) {
    point2 = secondDot;
}
