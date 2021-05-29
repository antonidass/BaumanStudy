#ifndef DRAWER_H
#define DRAWER_H

#include "ui_mainwindow.h"
#include "../objects/point.h"

class baseDrawer {
public:
    baseDrawer() = default;
    virtual ~baseDrawer() = default;
    virtual void drawLine(const Point &point1, const Point &point2) = 0;
    virtual void clearScene() = 0;
};


class qtDrawer : public baseDrawer {
public:
    qtDrawer();
    qtDrawer(QGraphicsScene *scene);
    qtDrawer(const qtDrawer &drawer);

    virtual void drawLine(const Point &point1, const Point &point2) override;
    virtual void clearScene() override;

private:
    QGraphicsScene *scene;
};

#endif
