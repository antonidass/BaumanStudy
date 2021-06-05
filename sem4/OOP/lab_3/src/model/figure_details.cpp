#include "../../inc/model/figure_details.h"
#include <utility>

FigureDetails::FigureDetails(std::vector<Point> &dots, std::vector<Link> &links) :
        _center{}, _points(dots), _links(links) {}

FigureDetails::FigureDetails(std::vector<Point> &dots, std::vector<Link> &links, Point center):
        _center(center), _points(dots), _links(links) {}

const std::vector<Point> &FigureDetails::getPoints() const {
    return _points;
}

std::vector<Point> &FigureDetails::getPoints() {
    return _points;
}




const std::vector<Link> &FigureDetails::getLinks() const {
    return _links;
}

const Point &FigureDetails::getCenter() const {
    return _center;
}

void FigureDetails::addPoint(const Point &dot) {
    _points.push_back(dot);
}

void FigureDetails::addLink(const Link &link) {
    _links.push_back(link);
}

void FigureDetails::transform(const Point &move, const Point &scale, const Point &rotate) {
    _center.move(move.getX(), move.getY(), move.getZ());

    for (auto &dot : _points) {
        dot.scale (scale.getX(), scale.getY(), scale.getZ());
        dot.rotate(rotate.getX(), rotate.getY(), rotate.getZ());
    }
}
