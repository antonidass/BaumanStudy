#include <utility>
#include "../../../inc/managers/scene/scene_manager.h"

SceneManager::SceneManager()
{
    _scene = std::make_shared<Scene>();
}

std::shared_ptr<Scene> SceneManager::get_scene() const
{
    return _scene;
}

std::shared_ptr<Camera> SceneManager::get_camera() const
{
    return _camera;
}

void SceneManager::set_scene(std::shared_ptr<Scene> scene)
{
    _scene = std::move(scene);
}

void SceneManager::set_camera(const size_t &camera_index)
{
    auto camera = _scene->get_cameras().at(camera_index);

    _camera = camera;
}
