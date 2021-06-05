#include "../../../inc/managers/load/load_manager_creator.h"

void CreatorLoadManager::makeInstance() {
    static std::shared_ptr<LoadManager> manager(new LoadManager());
    _manager = manager;
}

std::shared_ptr<LoadManager> CreatorLoadManager::create_manager() {
    if (nullptr == _manager) {
        makeInstance();
    }
    return _manager;
}

std::shared_ptr<LoadManager> CreatorLoadManager::create_manager(const std::shared_ptr <LoadSceneController> &loader) {
    if (nullptr == _manager) {
        makeInstance();
    }
    _manager->set_loader(loader);
    return _manager;
}

std::shared_ptr<LoadManager> CreatorLoadManager::create_manager(const std::shared_ptr <LoadModelController> &loader) {
    if (nullptr == _manager) {
        makeInstance();
    }
    _manager->set_loader(loader);
    return _manager;
}
