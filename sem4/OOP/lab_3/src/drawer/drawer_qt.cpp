#include "../../inc/drawer/drawer_qt.h"

DrawerQt::DrawerQt(QGraphicsScene *scene) {
    _scene = scene;
}

DrawerQt::DrawerQt(const DrawerQt &drawer) {
    _scene = drawer._scene;
}

void DrawerQt::drawLine(const Point &dot1, const Point &dot2) {
    _scene->addLine(dot1.getX(), dot1.getY(), dot2.getX(), dot2.getY());
}

void DrawerQt::clearScene() {
    _scene->clear();
}

