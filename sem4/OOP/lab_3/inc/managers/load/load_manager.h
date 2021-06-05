#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>

#include "../../object/figure.h"
#include "base_load_controller.h"
#include "load_scene_controller.h"
#include "load_model_controller.h"

class LoadManager {
public:
    LoadManager();
    LoadManager(const LoadManager &manager) = delete;
    LoadManager &operator = (const LoadManager &manager) = delete;

    ~LoadManager() = default;

    virtual std::shared_ptr<Scene> loadScene(std::string &name);
    virtual std::shared_ptr<Object> loadObject(std::string &name);

    virtual void set_loader(std::shared_ptr<LoadSceneController> loader);
    virtual void set_loader(std::shared_ptr<LoadModelController> loader);

private:
    std::shared_ptr<LoadSceneController> _loaderScene;
    std::shared_ptr<LoadModelController> _loaderFigure;
};

#endif
