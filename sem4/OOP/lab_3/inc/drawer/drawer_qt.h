#ifndef DRAWER_QT_H
#define DRAWER_QT_H

#include <QGraphicsScene>
#include "abstract_drawer.h"

class DrawerQt : public AbstractDrawer {
public:
    DrawerQt() = delete;
    explicit DrawerQt(QGraphicsScene *scene);
    DrawerQt(const DrawerQt &drawer);

    void drawLine(const Point &dot1, const Point &dot2) override;
    void clearScene() override;

private:
    QGraphicsScene *_scene;
};

#endif
