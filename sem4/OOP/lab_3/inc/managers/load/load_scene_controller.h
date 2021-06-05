#ifndef LOAD_SCENE_CONTROLLER_H
#define LOAD_SCENE_CONTROLLER_H

#include "base_load_controller.h"
#include "../../loader/base_loader_scene.h"
#include "../../loader/base_loader.h"
#include "../../builder/builder_scene.h"


class LoadSceneController : public BaseLoadController {
public:
    explicit LoadSceneController(std::shared_ptr<BaseLoaderScene> loader);
    ~LoadSceneController() = default;

    std::shared_ptr<Scene> load(std::string &file_name);

private:
    std::shared_ptr<BuilderScene> _builder;
    std::shared_ptr<BaseLoaderScene> _loader;
};

#endif
