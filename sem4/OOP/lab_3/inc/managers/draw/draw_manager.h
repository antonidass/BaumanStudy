#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "../../model/point.h"
#include "../../object/composite.h"
#include "../../object/object.h"

#include "../../drawer/abstract_drawer.h"
#include "../../../inc/scene/scene.h"
#include "../../../inc/managers/scene/scene_manager.h"

class Camera;

class DrawManager {
public:
    DrawManager() = default;
    DrawManager(const DrawManager &manager) = delete;
    DrawManager &operator = (const DrawManager &manager) = delete;
    ~DrawManager() = default;

    void setCamera(std::shared_ptr<Camera> viewer);
    void setScene(std::shared_ptr<Scene> scene);
    void setDrawer(std::shared_ptr<AbstractDrawer> drawer);

    void execute();
    Point getProection(const Point &dot);

private:
    std::shared_ptr<AbstractDrawer> _drawer;
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Scene> _scene;
};

#endif
