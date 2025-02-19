#ifndef LOAD_MANAGER_CREATOR_H
#define LOAD_MANAGER_CREATOR_H

#include <memory>

#include "load_manager.h"

class CreatorLoadManager {
public:
    std::shared_ptr<LoadManager> create_manager();
    std::shared_ptr<LoadManager> create_manager(const std::shared_ptr<LoadSceneController> &loader);
    std::shared_ptr<LoadManager> create_manager(const std::shared_ptr<LoadModelController> &loader);

private:
    void makeInstance();

    std::shared_ptr<LoadManager> _manager;
};

#endif
