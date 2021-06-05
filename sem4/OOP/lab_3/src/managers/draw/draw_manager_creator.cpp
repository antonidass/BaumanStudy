#include "../../../inc/managers/draw/draw_manager_creator.h"

std::shared_ptr<DrawManager> CreatorDrawManager::createManager() {
    if (nullptr == _manager) {
        makeInstance();
    }
    return _manager;
}

void CreatorDrawManager::makeInstance() {
    static std::shared_ptr<DrawManager> manager(new DrawManager());
    _manager = manager;
}
