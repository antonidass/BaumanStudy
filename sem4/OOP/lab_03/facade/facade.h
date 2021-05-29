#ifndef FACADE_H
#define FACADE_H

#include "../load/loader.h"
#include "../managers/managers.h"
#include "../visitor/visitor.h"


class Facade {
public:
    ~Facade() = default;
    Facade();

    void loadFigure(string fileName);
    void addFigure(const shared_ptr<Component> &);

    void addCamera(const Point &cameraPosition);
    void setCamera(const size_t &num);

    void drawScene(shared_ptr<baseDrawer> drawer);

    void transformFigure(const size_t &num, const Point &move, const Point &scale, const Point &rotate);
    void transformCamera(const size_t &num, const Point &shift);

    size_t camsCount();
    size_t figuresCount();

private:
    sceneManager managerScene;
    transformManager managerTransform;
    shared_ptr<abstractLoader> managerLoad;
    shared_ptr<drawManager> managerDraw;
};

#endif
