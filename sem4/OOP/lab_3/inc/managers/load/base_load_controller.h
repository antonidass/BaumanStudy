#ifndef ABSTRACT_LOAD_CONTROLLER_H
#define ABSTRACT_LOAD_CONTROLLER_H

#include <memory>

#include "../../builder/base_builder.h"
#include "../../loader/base_loader.h"
#include "../../scene/scene.h"

class Figure;
class BaseLoader;

class BaseLoadController {
public:
    BaseLoadController() = default;
    ~BaseLoadController() = default;
    virtual void setLoader(std::shared_ptr<BaseLoader> loader);

protected:
    std::shared_ptr<BaseLoader> _loader;
};

#endif

