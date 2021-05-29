#ifndef MANAGERS_H
#define MANAGERS_H


#include <memory>
#include "../gui/drawer.h"
#include "../visitor/visitor.h"
#include "../objects/component.h"
#include "../scene/scene.h"
using namespace std;


class baseManager {
public:
    baseManager() = default;
    ~baseManager() = default;
};


class drawManager : public Visitor, public baseManager {
public:
    drawManager() = default;
    drawManager(drawManager &manager);
    ~drawManager() = default;

    virtual void visit(const CameraComponent &cam) override;
    virtual void visit(const FigureComponent &figure) override;
    virtual void visit(const Composite &composite) override;

    void setDrawer(shared_ptr<baseDrawer>);
    void setCam(shared_ptr<CameraComponent>);

private:
    Point proectPoint(const Point &point);
    shared_ptr<baseDrawer> drawer;
    shared_ptr<CameraComponent> cam;
};


class transformManager : public baseManager {
public:
    transformManager() = default;
    ~transformManager() = default;

    void transformComponent(shared_ptr<Component> component, const Point &move, const Point &scale, const Point &rotate);
    void moveComponent(shared_ptr<Component> component, const double &dx, const double &dy, const double &dz);
    void scaneComponent(shared_ptr<Component> component, const double &kx, const double &ky, const double &kz);
    void rotateComponent(shared_ptr<Component> component, const double &ox, const double &oy, const double &oz);
};


class sceneManager : public baseManager {
public:
    sceneManager();
    ~sceneManager() = default;

    shared_ptr<Scene> getScene() const;
    shared_ptr<CameraComponent> getCam() const;

    void setScene(shared_ptr<Scene> scene);
    void setCam(const size_t &num);

private:
    shared_ptr<Scene> scene;
    shared_ptr<CameraComponent> currentCam;
};


#endif
