#include "../../inc/camera/camera.h"

void Camera::move_x(const double &dx)
{
    _position.set_x(_position.get_x() + dx);
}

void Camera::move_y(const double &dy)
{
    _position.set_y(_position.get_y() + dy);
}

void Camera::move_z(const double &dz)
{
    _position.set_z(_position.get_z() + dz);
}

void Camera::transform(const Dot &new_position, const Dot &scale, const Dot &rotate)
{
    move_x(new_position.get_x());
    move_y(new_position.get_y());
}

void Camera::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
