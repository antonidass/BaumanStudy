#include "../../inc/builder/builder_scene.h"

void BuilderScene::build() {
    _scene_ptr = std::make_shared<Scene>();
}

void BuilderScene::buildFigure(const std::shared_ptr<Object> &object) {
    _scene_ptr->addFigure(object);
}

void BuilderScene::buildCamera(const std::shared_ptr<Camera> &camera) {
    _scene_ptr->addCamera(camera);
}

bool BuilderScene::isBuild() const {
    return nullptr != _scene_ptr;
}

std::shared_ptr<Scene> BuilderScene::get() {
    return _scene_ptr;
}
