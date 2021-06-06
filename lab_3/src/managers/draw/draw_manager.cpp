#include "../../../inc/managers/draw/draw_manager.h"
#include "../../../inc/model/model.h"
#include "../../../inc/camera/camera.h"

void DrawManager::set_camera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void DrawManager::set_drawer(std::shared_ptr<AbstractDrawer> drawer)
{
    _drawer = drawer;
}

Dot DrawManager::get_dot_proection(const Dot &dot)
{
    Dot proection = dot;

    proection.set_x(proection.get_x() + _camera->_position.get_x());
    proection.set_y(proection.get_y() + _camera->_position.get_y());

    return proection;
}

void DrawManager::visit(const Model &model)
{
    auto dots   = model._modelStructure->get_dots();
    auto links  = model._modelStructure->get_links();
    auto center = model._modelStructure->get_center();

    for (auto link : links)
    {
        _drawer->draw_line(get_dot_proection(dots.at(link.get_dot1_index())).with_center(center),
                           get_dot_proection(dots.at(link.get_dot2_index())).with_center(center));
    }
}
