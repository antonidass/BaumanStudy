#include "../../../inc/managers/transform/transform_manager_creator.h"


void CreatorTransformManager::makeInstance() {
    static std::shared_ptr<TransformManager> manager(new TransformManager());
    _manager = manager;
}


std::shared_ptr<TransformManager> CreatorTransformManager::create_manager() {
    if (nullptr == _manager) {
        makeInstance();
    }
    return _manager;
}
