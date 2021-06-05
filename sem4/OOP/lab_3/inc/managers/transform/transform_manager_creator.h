#ifndef TRANSFORM_MANAGER_CREATOR_H
#define TRANSFORM_MANAGER_CREATOR_H

#include "transform_manager.h"

class CreatorTransformManager {
public:
    std::shared_ptr<TransformManager> create_manager();
private:
    void makeInstance();
    std::shared_ptr<TransformManager> _manager;
};

#endif //TRANSFORM_MANAGER_CREATOR_H
