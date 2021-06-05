#ifndef MODEL_STRUCTURE_H
#define MODEL_STRUCTURE_H

#include <vector>

#include "point.h"
#include "link.h"

class FigureDetails {
public:
    FigureDetails() = default;
    FigureDetails(std::vector<Point> &dots, std::vector<Link> &links);
    FigureDetails(std::vector<Point> &dots, std::vector<Link> &links, Point center);
    ~FigureDetails() = default;

    const std::vector<Point> &getPoints() const;
    std::vector<Point> &getPoints();

    const std::vector<Link> &getLinks() const;
    const Point &getCenter() const;

    void addPoint (const Point &dot);
    void addLink (const Link &link);
    void transform(const Point &move, const Point &scale, const Point &spin);

private:
    Point _center;
    std::vector<Point> _points;
    std::vector<Link> _links;
};

#endif
