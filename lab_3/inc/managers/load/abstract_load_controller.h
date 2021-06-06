#ifndef ABSTRACT_LOAD_CONTROLLER_H
#define ABSTRACT_LOAD_CONTROLLER_H

#include <memory>

#include "../../builder/base_builder.h"
#include "../../loader/base_loader.h"

class Model;
class BaseLoader;

class AbstractLoadController
{
public:
    AbstractLoadController() = default;
    ~AbstractLoadController() = default;

    virtual std::shared_ptr<Object> load(std::string &name) = 0;
    virtual void set_loader(std::shared_ptr<BaseLoader> loader);

protected:
    std::shared_ptr<BaseLoader> _loader;
};

#endif

