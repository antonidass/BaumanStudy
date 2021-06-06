#include "../../../inc/managers/load/load_model_controller_creator.h"
#include "../../../inc/configuration/creator_cfg.h"
#include "../../../inc/loader/loader_model_file.h"

std::shared_ptr<LoadModelController> LoadModelControllerCreator::create_controller()
{
    if (nullptr == _controller)
    {
        create_instance();
    }

    return _controller;
}

std::shared_ptr<LoadModelController> LoadModelControllerCreator::create_controller(const std::shared_ptr<BaseLoaderModel> &loader)
{
    if (nullptr == _controller)
    {
        create_instance();
    }

    _controller->set_loader(loader);

    return _controller;
}

void LoadModelControllerCreator::create_instance()
{
    static std::shared_ptr<LoadModelController> controller;

    if (!controller)
    {
        std::shared_ptr<BaseLoaderModel> loader;

        switch (CreatorConfig().get_config()->get_load_source())
        {
            case AbstractConfig::FILE:

            default:
                loader = std::shared_ptr<BaseLoaderModel>(new ModelLoaderFile);
        }

        controller = std::make_shared<LoadModelController>(loader);
    }

    _controller = controller;
}
