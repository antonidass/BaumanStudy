#ifndef SCENE_H
#define SCENE_H

#include "ui_mainwindow.h"
#include "../objects/component.h"


class Scene {
public:
    Scene();
    ~Scene() = default;

    void addFigure(shared_ptr<Component> figureComp);
    void addCamera(const shared_ptr<CameraComponent> &camera);

    Vector<shared_ptr<Component>> getFigures();
    shared_ptr<Composite> getComposite();
    Vector<shared_ptr<CameraComponent>> getCams();

protected:
    shared_ptr<Composite> figures;
    Vector<shared_ptr<CameraComponent>> cams;
};

#endif
