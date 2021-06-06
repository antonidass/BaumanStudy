#include <iterator>
#include "../../inc/scene/scene.h"
#include "../../inc/object/composite.h"

Scene::Scene() : _models(new Composite) {};

std::vector<std::shared_ptr<Object>> Scene::get_models()
{
    return _models->_elements;
}

std::vector<std::shared_ptr<Camera>> Scene::get_cameras()
{
    return _cameras;
}

std::shared_ptr<Composite> Scene::get_composite()
{
    return _models;
}

void Scene::add_model(const std::shared_ptr<Object> &model)
{
    _models->add(model);
}

void Scene::remove_model(const std::size_t index)
{
    auto iter = _models->begin();

    std::advance(iter, index);
    _models->remove(iter);
}

void Scene::add_camera(const std::shared_ptr<Camera> &camera)
{
    _cameras.push_back(camera);
}

void Scene::remove_camera(const std::size_t index)
{
    auto iter = _cameras.begin();

    std::advance(iter, index);
    _cameras.erase(iter);
}
