#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "../base_manager.h"
#include "../../model/dot.h"
#include "../../object/composite.h"
#include "../../object/object.h"

#include "../../drawer/abstract_drawer.h"
#include "../../visitor/visitor.h"

class Camera;

class DrawManager : public BaseManager, public Visitor
{
public:
    DrawManager() = default;
    DrawManager(const DrawManager &manager) = delete;
    DrawManager &operator = (const DrawManager &manager) = delete;
    ~DrawManager() = default;

    void set_camera(std::shared_ptr<Camera> viewer);
    void set_drawer(std::shared_ptr<AbstractDrawer> drawer);

    void visit(const Model &model) override;
    void visit(const Camera &camera) override {};
    void visit(const Composite &composite) override {};

    Dot get_dot_proection(const Dot &dot);

private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<AbstractDrawer> _drawer;

};

#endif
