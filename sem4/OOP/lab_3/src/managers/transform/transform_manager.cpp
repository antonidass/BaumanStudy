#include "../../../inc/managers/transform/transform_manager.h"

void TransformManager::moveObject(const std::shared_ptr <Object> &object, const double &dx, const double &dy, const double &dz) {
    MoveVisitor moveVisitor(dx, dy, dz);

    if (object->isVisible()) {
        std::shared_ptr<Figure> figure = std::static_pointer_cast<Figure>(object);
        moveVisitor.visit(figure);
    }
    else {
        std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(object);
        moveVisitor.visit(cam);
    }
}

void TransformManager::scaleObject(const std::shared_ptr <Object> &object, const double &kx, const double &ky, const double &kz) {
    ScaleVisitor scaleVisitor(kx, ky, kz);

    if (object->isVisible()) {
        std::shared_ptr<Figure> figure = std::static_pointer_cast<Figure>(object);
        scaleVisitor.visit(figure);
    }
    else {
        std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(object);
        scaleVisitor.visit(cam);
    }
}

void TransformManager::spinObject(const std::shared_ptr <Object> &object, const double &ox, const double &oy, const double &oz) {
    RotateVisitor rotateVisitor(ox, oy, oz);

    if (object->isVisible()) {
        std::shared_ptr<Figure> figure = std::static_pointer_cast<Figure>(object);
        rotateVisitor.visit(figure);
    }
    else {
        std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(object);
        rotateVisitor.visit(cam);
    }
}