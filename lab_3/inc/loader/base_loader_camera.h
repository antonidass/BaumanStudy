#ifndef LOADER_VIEWER_H
#define LOADER_VIEWER_H

#include "base_loader.h"
#include "../builder/builder_camera.h"

class BaseLoaderCamera : public BaseLoader
{
public:
    virtual std::shared_ptr<Object> load(std::shared_ptr<BuilderCamera> builder) = 0;
};

#endif
