
#include "../../inc/builder/builder_camera.h"

void BuilderCamera::build()
{
    _camera_ptr = std::make_shared<Camera>();
}

void BuilderCamera::build_position(const double x, const double y, const double z) {}

bool BuilderCamera::is_build() const
{
    return nullptr != _camera_ptr;
}

std::shared_ptr<Object> BuilderCamera::get()
{
    return _camera_ptr;
}

