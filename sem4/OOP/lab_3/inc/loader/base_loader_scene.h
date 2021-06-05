#ifndef BASE_LOADER_SCENE_H
#define BASE_LOADER_SCENE_H

#include "base_loader.h"
#include "../builder/builder_scene.h"

class BaseLoaderScene : public BaseLoader {
public:
    virtual std::shared_ptr<Scene> load(std::shared_ptr<BuilderScene> builder) = 0;

protected:
    virtual void loadModels (std::shared_ptr<BuilderScene> builder) = 0;
    virtual void loadCameras (std::shared_ptr<BuilderScene> builder) = 0;
};

#endif
