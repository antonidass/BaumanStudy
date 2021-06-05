#ifndef DRAW_MANAGER_CREATOR_H
#define DRAW_MANAGER_CREATOR_H

#include "draw_manager.h"

class CreatorDrawManager {
public:
    std::shared_ptr<DrawManager> createManager();
private:
    void makeInstance();
    std::shared_ptr<DrawManager> _manager;
};

#endif
