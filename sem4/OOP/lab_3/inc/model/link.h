#ifndef LINK_H
#define LINK_H

#include <cstddef>

class Link {
public:
    Link() = default;
    Link(const Link &_link) = default;
    Link(const std::size_t &dot1, const std::size_t &dot2);
    ~Link() = default;

    std::size_t getFirstPoint() const;
    std::size_t getSecondPoint() const;

    void setFirstPoint(const std::size_t &firstDot);
    void setSecondPoint(const std::size_t &secondDot);

private:
    std::size_t point1;
    std::size_t point2;
};

#endif
