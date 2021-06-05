#include "../../../inc/managers/scene/scene_manager_creator.h"

std::shared_ptr<SceneManager> CreatorSceneManager::createManager() {
    if (nullptr == _manager) {
        makeInstance();
    }
    return _manager;
}

void CreatorSceneManager::makeInstance() {
    static std::shared_ptr<SceneManager> manager(new SceneManager());
    _manager = manager;
}
