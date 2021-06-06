#ifndef LOAD_SCENE_CONTROLLER_CREATOR_H
#define LOAD_SCENE_CONTROLLER_CREATOR_H

#include "load_scene_controller.h"

class LoadSceneControllerCreator
{
public:
    std::shared_ptr<LoadSceneController> create_controller();
    std::shared_ptr<LoadSceneController> create_controller(const std::shared_ptr<BaseLoaderScene> &loader);

private:
    void create_instance();

    std::shared_ptr<LoadSceneController> _controller;
};

#endif
