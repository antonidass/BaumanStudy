#ifndef LINK_H
#define LINK_H

#include <stdlib.h>

class Link {
public:
    Link();
    Link(const size_t &pt1, const size_t &pt2);
    Link(const Link &link);
    ~Link() = default;

    size_t getFirst() const;
    size_t getSecond() const;

    void getFirst(const size_t &first);
    void getSecond(const size_t &second);

private:
    size_t pt1_index, pt2_index;
};

#endif
