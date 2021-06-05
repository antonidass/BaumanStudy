#include <iterator>
#include "../../inc/scene/scene.h"
#include "../../inc/object/composite.h"

Scene::Scene() : _figures(new Composite) {};

std::vector<std::shared_ptr<Object>> Scene::getFigures() {
    return _figures->_elements;
}

std::vector<std::shared_ptr<Camera>> Scene::getCameras() {
    return _cameras;
}

std::shared_ptr<Composite> Scene::getComposite() {
    return _figures;
}

void Scene::addFigure(const std::shared_ptr<Object> &figure) {
    _figures->add(figure);
}

void Scene::removeFigure(const std::size_t index) {
    auto iter = _figures->begin();

    std::advance(iter, index);
    _figures->remove(iter);
}

void Scene::addCamera(const std::shared_ptr<Camera> &camera) {
    _cameras.push_back(camera);
}

void Scene::removeCamera(const std::size_t index) {
    auto iter = _cameras.begin();

    std::advance(iter, index);
    _cameras.erase(iter);
}
