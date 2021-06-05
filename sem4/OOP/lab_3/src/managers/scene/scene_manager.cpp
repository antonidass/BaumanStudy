#include <utility>
#include "../../../inc/managers/scene/scene_manager.h"

SceneManager::SceneManager() {
    _scene = std::make_shared<Scene>();
}

std::shared_ptr<Scene> SceneManager::getScene() const {
    return _scene;
}

std::shared_ptr<Camera> SceneManager::getCamera() const {
    return _camera;
}

void SceneManager::setScene(std::shared_ptr<Scene> scene) {
    _scene = std::move(scene);
}



void SceneManager::setCamera(const size_t &cameraIndex) {
    auto camera = _scene->getCameras().at(cameraIndex);
    _camera = camera;
}
