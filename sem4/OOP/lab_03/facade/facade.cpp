#include "facade.h"


void Facade::loadFigure(string fname) {
    shared_ptr<FigureComponent> model = this->managerLoad->loadFigure(fname);
    this->managerScene.getScene()->addFigure(model);
}


void Facade::addFigure(const shared_ptr<Component> &figure) {
    this->managerScene.getScene()->addFigure(figure);
}


void Facade::addCamera(const Point &cameraPosition) {
    shared_ptr<CameraComponent> cam(new CameraComponent);
    cam->transform(cameraPosition, cameraPosition, cameraPosition);

    this->managerScene.getScene()->addCamera(cam);
    this->managerScene.setCam(managerScene.getScene()->getCams().getSize() - 1);
}



void Facade::transformFigure(const size_t &num, const Point &move, const Point &scale, const Point &rotate) {
    shared_ptr<Component> figure = managerScene.getScene()->getFigures().at(num - 1);
    this->managerTransform.transformComponent(figure, move, scale, rotate);
}


void Facade::setCamera(const size_t &num) {
    managerScene.setCam(num);
}

void Facade::drawScene(shared_ptr<baseDrawer> drawer) {
    drawer->clearScene();
    managerDraw->setDrawer(drawer);
    managerDraw->setCam(managerScene.getCam());
    managerScene.getScene()->getComposite()->accept(managerDraw);
}


void Facade::transformCamera(const size_t &num, const Point &shift) {
    auto camera = managerScene.getScene()->getCams().at(num - 1);
    this->managerTransform.transformComponent(camera, shift, shift, shift);
}


size_t Facade::camsCount() {
    return managerScene.getScene()->getCams().getSize();
}


size_t Facade::figuresCount() {
    return managerScene.getScene()->getCams().getSize();
}


Facade::Facade() {
    this->managerDraw = shared_ptr<drawManager>(new drawManager);
    shared_ptr<baseLoader> floader(new fileLoader);
    this->managerLoad = shared_ptr<abstractLoader>(new figureLoader(floader));
}

