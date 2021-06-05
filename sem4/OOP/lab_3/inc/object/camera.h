#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"
#include "../model/point.h"
#include "../managers/draw/draw_manager.h"


class Camera : public Object {
    friend Point DrawManager::getProection(const Point &dot);

public:
    Camera() = default;
    explicit Camera(const Point &pos) : _pos(pos) {};
    ~Camera() override = default;

    virtual bool isVisible();

    bool isComposite() override;
    void accept(Visitor *visitor) override;

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);

private:
    void moveX(const double &dx);
    void moveY(const double &dy);
    void moveZ(const double &dz);

    Point _pos;

};

#endif
