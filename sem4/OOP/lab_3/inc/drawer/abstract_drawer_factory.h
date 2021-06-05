#ifndef DRAWER_FACTORY_H
#define DRAWER_FACTORY_H

#include <memory>
#include "abstract_drawer.h"

class AbstractDrawerFactory {
public:
    virtual std::unique_ptr<AbstractDrawer> graphicCreate() = 0;
};

#endif
