#include "../../../inc/managers/load/load_model_controller_creator.h"
#include "../../../inc/configuration/creator_cfg.h"
#include "../../../inc/loader/loader_figure_file.h"

std::shared_ptr<LoadModelController> LoadModelControllerCreator::createController() {
    if (nullptr == _controller) {
        makeInstance();
    }

    return _controller;
}

std::shared_ptr<LoadModelController> LoadModelControllerCreator::createController(const std::shared_ptr<BaseLoaderFigure> &loader) {
    if (nullptr == _controller) {
        makeInstance();
    }
    _controller->setLoader(loader);
    return _controller;
}

void LoadModelControllerCreator::makeInstance() {
    static std::shared_ptr<LoadModelController> controller;
    if (!controller) {
        std::shared_ptr<BaseLoaderFigure> loader;
        switch (CreatorConfig().get_config()->get_load_source()) {
            case AbstractConfig::FILE:

            default:
                loader = std::shared_ptr<BaseLoaderFigure>(new FigureLoaderFile);
        }
        controller = std::make_shared<LoadModelController>(loader);
    }

    _controller = controller;
}
