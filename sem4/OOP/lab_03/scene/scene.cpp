#include "scene.h"

Scene::Scene() : figures(new Composite) {}

void Scene::addFigure(std::shared_ptr<Component> modelComponent) {
    this->figures->add(modelComponent);
}


void Scene::addCamera(const std::shared_ptr<CameraComponent> &camera) {
    this->cams.pushBack(camera);
}


Vector<std::shared_ptr<Component>> Scene::getFigures() {
    return this->figures->getObjects();
}

std::shared_ptr<Composite> Scene::getComposite() {
    return this->figures;
}

Vector<std::shared_ptr<CameraComponent>> Scene::getCams() {
    return this->cams;
}


