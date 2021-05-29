#include "command.h"


loadFigure::loadFigure(const string &fileName) {
    this->fileName = fileName;
}

void loadFigure::execute(shared_ptr<Facade> &facade) {
    facade->loadFigure(this->fileName);
}


addFigure::addFigure(const shared_ptr<Component> &model) {
    this->figure = model;
}

void addFigure::execute(shared_ptr<Facade> &facade) {
    facade->addFigure(figure);
}




moveFigure::moveFigure(const double &dx, const double &dy, const double &dz, const size_t &num) {
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->num = num;
}


void moveFigure::execute(shared_ptr<Facade> &facade) {
    Point move(dx, dy, dz);
    Point scale(1, 1, 1);
    Point turn(0, 0, 0);

    facade->transformFigure(num, move, scale, turn);
}


scaleFigure::scaleFigure(const double &kx, const double &ky, const double &kz, const size_t &num) {
    this->kx = kx;
    this->ky = ky;
    this->kz = kz;
    this->num = num;
}


void scaleFigure::execute(shared_ptr<Facade> &facade) {
    Point move(0, 0, 0);
    Point scale(kx, ky, kz);
    Point turn(0, 0, 0);

    facade->transformFigure(num, move, scale, turn);
}


rotateFigure::rotateFigure(const double &ox, const double &oy, const double &oz, const size_t &num) {
    this->ox = ox;
    this->oy = oy;
    this->oz = oz;
    this->num = num;
}



void rotateFigure::execute(shared_ptr<Facade> &facade) {
    Point move(0, 0, 0);
    Point scale(1, 1, 1);
    Point turn(ox, oy, oz);

    facade->transformFigure(num, move, scale, turn);
}

transformFigure::transformFigure(const size_t &num, const Point &move, const Point &scale, const Point &rotate) {
    this->move = move;
    this->scale = scale;
    this->rotate = rotate;
    this->num = num;
}


void transformFigure::execute(shared_ptr<Facade> &facade) {
    facade->transformFigure(num, move, scale, rotate);
}


addCamera::addCamera(const double x, const double y, const double z) {
    this->xPos = x;
    this->yPos = y;
    this->zPos = z;
}


void addCamera::execute(shared_ptr<Facade> &facade) {
    Point cam_pos(xPos, yPos, zPos);
    facade->addCamera(cam_pos);
}




moveCamera::moveCamera(const size_t &num, const double &ox, const double &oy) {
    this->ox = ox;
    this->oy = oy;
    this->num = num;
}


void moveCamera::execute(shared_ptr<Facade> &facade) {
    Point shift(ox, oy, 0);
    facade->transformCamera(num, shift);
}


drawScene::drawScene(shared_ptr<baseDrawer> drawer) {
    this->drawer = drawer;
}


void drawScene::execute(shared_ptr<Facade> &facade) {
    facade->drawScene(drawer);
}
