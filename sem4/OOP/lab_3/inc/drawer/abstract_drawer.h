#ifndef ABSTRACT_DRAWER_H
#define ABSTRACT_DRAWER_H

#include "../model/point.h"

class AbstractDrawer {
public:
    AbstractDrawer() = default;
    virtual ~AbstractDrawer() = default;

    virtual void drawLine(const Point &dot1, const Point &dot2) = 0;
    virtual void clearScene() = 0;
};

#endif
