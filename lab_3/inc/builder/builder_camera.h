#ifndef BUILDER_CAMERA_H
#define BUILDER_CAMERA_H

#include "../camera/camera.h"
#include "base_builder.h"

class BuilderCamera : public BaseBuilder
{
public:
    BuilderCamera() = default;
    ~BuilderCamera() = default;

    void build() override;
    void build_position(const double x, const double y, const double z);
    bool is_build() const override;

    std::shared_ptr<Object> get() override;

private:
    std::shared_ptr<Camera> _camera_ptr;
};

#endif
