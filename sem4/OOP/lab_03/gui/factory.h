#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "drawer.h"
using namespace std;

class abstractFactory {
public:
    virtual unique_ptr<baseDrawer> createGraphics() = 0;
};

class qtFactory : public abstractFactory {
public:
    virtual unique_ptr<baseDrawer> createGraphics() override;
};

#endif
