#ifndef BASE_LOADER_MODEL_H
#define BASE_LOADER_MODEL_H

#include "base_loader.h"
#include "../builder/builder_figure.h"

class BaseLoaderFigure : public BaseLoader {
public:
    virtual std::shared_ptr<Object> load(std::shared_ptr<BuilderFigure> builder) = 0;
};

#endif
