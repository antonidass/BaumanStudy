#include "../../../inc/managers/draw/draw_manager.h"
#include "../../../inc/object/figure.h"
#include "../../../inc/object/camera.h"

void DrawManager::setCamera(std::shared_ptr<Camera> viewer) {
    _camera = viewer;
}

void DrawManager::setDrawer(std::shared_ptr<AbstractDrawer> drawer) {
    _drawer = drawer;
}

void DrawManager::setScene(std::shared_ptr<Scene> scene) {
    _scene = std::move(scene);
}


void DrawManager::execute() {
    for (auto obj : *(_scene->getComposite().get())) {
        std::shared_ptr<Figure> figure = std::static_pointer_cast<Figure>(obj);
            auto dots = figure->_figureDetails->getPoints();
            auto links = figure->_figureDetails->getLinks();
            auto center = figure->_figureDetails->getCenter();
            for (auto link : links) {
                _drawer->drawLine(getProection(dots.at(link.getFirstPoint())).withCenter(center),
                                  getProection(dots.at(link.getSecondPoint())).withCenter(center));
        }
    }
}

Point DrawManager::getProection(const Point &dot) {
    Point proection = dot;
    proection.setX(proection.getX() + _camera->_pos.getX());
    proection.setY(proection.getY() + _camera->_pos.getY());
    return proection;
}

