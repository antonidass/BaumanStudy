#ifndef CAMERA_H
#define CAMERA_H

#include "../object/object.h"
#include "../managers/draw/draw_manager.h"

class Camera : public InvisibleObject
{
    friend Dot DrawManager::get_dot_proection(const Dot &dot);

public:
    Camera() = default;
    explicit Camera(const Dot &position) : _position(position) { };
    ~Camera() override = default;

    void transform(const Dot &new_position, const Dot &scale, const Dot &rotate) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

private:
    void move_x(const double &dx);
    void move_y(const double &dy);
    void move_z(const double &dz);

    Dot _position;
};

#endif
