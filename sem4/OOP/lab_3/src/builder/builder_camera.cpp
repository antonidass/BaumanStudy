
#include "../../inc/builder/builder_camera.h"

void BuilderCamera::build() {
    _camera_ptr = std::make_shared<Camera>();
}

bool BuilderCamera::isBuild() const {
    return nullptr != _camera_ptr;
}

std::shared_ptr<Object> BuilderCamera::get() {
    return _camera_ptr;
}

