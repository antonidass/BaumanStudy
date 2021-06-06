#include "../../../inc/managers/load/load_scene_controller_creator.h"
#include "../../../inc/configuration/configuration.h"
#include "../../../inc/configuration/creator_cfg.h"
#include "../../../inc/loader/loader_scene_file.h"

std::shared_ptr<LoadSceneController> LoadSceneControllerCreator::create_controller()
{
    if (nullptr == _controller)
    {
        create_instance();
    }

    return _controller;
}

std::shared_ptr<LoadSceneController> LoadSceneControllerCreator::create_controller(const std::shared_ptr<BaseLoaderScene> &loader)
{
    if (nullptr == _controller)
    {
        create_instance();
    }

    _controller->set_loader(loader);

    return _controller;
}

void LoadSceneControllerCreator::create_instance()
{
    static std::shared_ptr<LoadSceneController> Controller;

    if (!Controller)
    {
        std::shared_ptr<BaseLoaderScene> loader;

        switch (CreatorConfig().get_config()->get_load_source())
        {
            case AbstractConfig::FILE:

            default:
                loader = std::shared_ptr<BaseLoaderScene>(new SceneLoaderFile);

        }

        Controller = std::make_shared<LoadSceneController>(loader);
    }

    _controller = Controller;
}
