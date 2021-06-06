#include "../../inc/model/model_struct.h"
#include <utility>

ModelStructure::ModelStructure(std::vector<Dot> &dots, std::vector<Link> &links) :
    _center{}, _dots(dots), _links(links) {}

ModelStructure::ModelStructure(std::vector<Dot> &dots, std::vector<Link> &links, Dot center):
    _center(center), _dots(dots), _links(links) {}

const std::vector<Dot> &ModelStructure::get_dots() const
{
    return _dots;
}

const std::vector<Link> &ModelStructure::get_links() const
{
    return _links;
}

const Dot &ModelStructure::get_center() const
{
    return _center;
}

void ModelStructure::add_dot(const Dot &dot)
{
    _dots.push_back(dot);
}

void ModelStructure::add_link(const Link &link)
{
    _links.push_back(link);
}

void ModelStructure::transform(const Dot &move, const Dot &scale, const Dot &rotate)
{
    _center.move(move.get_x(), move.get_y(), move.get_z());

    for (auto &dot : _dots)
    {
        dot.scale (scale.get_x(),  scale.get_y(),  scale.get_z());
        dot.rotate(rotate.get_x(), rotate.get_y(), rotate.get_z());
    }
}
