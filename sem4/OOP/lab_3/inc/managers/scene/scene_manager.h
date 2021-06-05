#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../../scene/scene.h"

class SceneManager {
public:
    SceneManager();
    SceneManager(const SceneManager &scene) = delete;
    SceneManager &operator = (const SceneManager &scene) = delete;
    ~SceneManager() = default;

    std::shared_ptr<Scene> getScene() const;
    std::shared_ptr<Camera> getCamera() const;

    void setScene(std::shared_ptr<Scene> scene);
    void setCamera(const std::size_t &cameraIndex);

protected:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Scene> _scene;
};

#endif
