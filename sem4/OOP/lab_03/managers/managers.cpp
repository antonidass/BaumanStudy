#include "managers.h"
#include "../objects/component.h"


drawManager::drawManager(drawManager &manager) : drawer(manager.drawer), cam(manager.cam) {}


void drawManager::setDrawer(shared_ptr<baseDrawer> drawer) {
    this->drawer = drawer;
}


void drawManager::setCam(shared_ptr<CameraComponent> newCam) {
    this->cam = newCam;
}


void drawManager::visit(const FigureComponent &figure) {
    auto points = figure.getFigure()->getPoints();
    for (auto link: figure.getFigure()->getLinks()) {
        this->drawer->drawLine(
                    proectPoint(points.at(link.getFirst())),
                    proectPoint(points.at(link.getSecond()))
        );
    }
}

void drawManager::visit(const CameraComponent &camera) {};
void drawManager::visit(const Composite &composite) {};

Point drawManager::proectPoint(const Point &point) {
    Point new_point(point);
    Point cam_pos(cam->getPosition());
    new_point.setX(new_point.getX() + cam_pos.getX());
    new_point.setY(new_point.getY() + cam_pos.getY());

    return new_point;
}







void transformManager::transformComponent(shared_ptr<Component> component, const Point &move, const Point &scale, const Point &rotate) {
    component->transform(move, scale, rotate);
}


void transformManager::moveComponent(shared_ptr<Component> component, const double &dx, const double &dy, const double &dz) {
    Point move(dx, dy, dz);
    Point scale(1, 1, 1);
    Point turn(0, 0, 0);
    component->transform(move, scale, turn);
}


void transformManager::scaneComponent(shared_ptr<Component> component, const double &kx, const double &ky, const double &kz) {
    Point move(0, 0, 0);
    Point scale(kx, ky, kz);
    Point turn(0, 0, 0);
    component->transform(move, scale, turn);
}


void transformManager::rotateComponent(shared_ptr<Component> component, const double &ox, const double &oy, const double &oz) {
    Point move(0, 0, 0);
    Point scale(1, 1, 1);
    Point turn(ox, oy, oz);
    component->transform(move, scale, turn);
}



sceneManager::sceneManager() {
    this->scene = shared_ptr<Scene>(new Scene);
}


shared_ptr<Scene> sceneManager::getScene() const {
    return this->scene;
}


shared_ptr<CameraComponent> sceneManager::getCam() const {
    return this->currentCam;
}


void sceneManager::setScene(shared_ptr<Scene> scene) {
    this->scene = scene;
}


void sceneManager::setCam(const size_t &num) {
    auto camera = scene->getCams().at(num);
    this->currentCam = camera;
}


