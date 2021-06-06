#ifndef LOAD_MODEL_CONTROLLER_CREATOR_H
#define LOAD_MODEL_CONTROLLER_CREATOR_H

#include "load_model_controller.h"

class LoadModelControllerCreator
{
public:
    std::shared_ptr<LoadModelController> create_controller();
    std::shared_ptr<LoadModelController> create_controller(const std::shared_ptr<BaseLoaderModel> &loader);

private:
    void create_instance();

    std::shared_ptr<LoadModelController> _controller;
};

#endif
