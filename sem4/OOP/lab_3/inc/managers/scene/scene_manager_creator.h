#ifndef CREATOR_SCENE_MANAGER_H
#define CREATOR_SCENE_MANAGER_H

#include <memory>
#include "scene_manager.h"

class CreatorSceneManager {
public:
    std::shared_ptr<SceneManager> createManager();

private:
    void makeInstance();
    std::shared_ptr<SceneManager> _manager;
};

#endif
