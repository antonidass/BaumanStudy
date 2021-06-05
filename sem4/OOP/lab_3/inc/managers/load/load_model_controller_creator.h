#ifndef LOAD_MODEL_CONTROLLER_CREATOR_H
#define LOAD_MODEL_CONTROLLER_CREATOR_H

#include "load_model_controller.h"

class LoadModelControllerCreator {
public:
    std::shared_ptr<LoadModelController> createController();
    std::shared_ptr<LoadModelController> createController(const std::shared_ptr<BaseLoaderFigure> &loader);

private:
    void makeInstance();
    std::shared_ptr<LoadModelController> _controller;
};

#endif
