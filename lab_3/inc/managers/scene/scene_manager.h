#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../base_manager.h"
#include "../../scene/scene.h"

class SceneManager : public BaseManager
{
public:
    SceneManager();
    SceneManager(const SceneManager &scene) = delete;
    SceneManager &operator = (const SceneManager &scene)  = delete;
    ~SceneManager() = default;

    std::shared_ptr<Scene>  get_scene() const;
    std::shared_ptr<Camera> get_camera() const;

    void set_scene(std::shared_ptr<Scene> scene);
    void set_camera(const std::size_t &camera_index);

private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Scene>  _scene;
};

#endif
