#include "drawer.h"

qtDrawer::qtDrawer() {
    scene = nullptr;
}

qtDrawer::qtDrawer(QGraphicsScene *scene) {
    this->scene = scene;
}

qtDrawer::qtDrawer(const qtDrawer &drawer) {
    this->scene = drawer.scene;
}

void qtDrawer::clearScene() {
    scene->clear();
}

void qtDrawer::drawLine(const Point &point1, const Point &point2) {
    this->scene->addLine(point1.getX(), point1.getY(), point2.getX(), point2.getY());
}
