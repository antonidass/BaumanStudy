#include "link.h"

Link::Link() : pt1_index(0), pt2_index(0) {}

Link::Link(const size_t &pt1, const size_t &pt2) : pt1_index(pt1), pt2_index(pt2) {}

Link::Link(const Link &link) {
    this->pt1_index = link.pt1_index;
    this->pt2_index = link.pt2_index;
}

size_t Link::getFirst() const {
    return this->pt1_index;
}

size_t Link::getSecond() const {
    return this->pt2_index;
}

void Link::getFirst(const size_t &figure) {
    this->pt1_index = figure;
}

void Link::getSecond(const size_t &second) {
    this->pt2_index = second;
}
