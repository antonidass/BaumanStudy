#include "../../inc/builder/builder_scene.h"

void BuilderScene::build()
{
    _scene_ptr = std::make_shared<Scene>();
}

void BuilderScene::build_model(const std::shared_ptr<Object> &object)
{
    if (is_build()) {}

    _scene_ptr->add_model(object);
}

void BuilderScene::build_camera(const std::shared_ptr<Camera> &camera)
{
    if (is_build()) {}

    _scene_ptr->add_camera(camera);
}

bool BuilderScene::is_build() const
{
    return nullptr != _scene_ptr;
}

std::shared_ptr<Object> BuilderScene::get()
{
    return _scene_ptr;
}
