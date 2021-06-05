#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "../object/object.h"

class BaseBuilder {
public:
     BaseBuilder() = default;
    ~BaseBuilder() = default;

    virtual void build() = 0;
    virtual bool isBuild() const = 0;
};

#endif
