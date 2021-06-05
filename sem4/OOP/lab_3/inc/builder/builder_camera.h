#ifndef BUILDER_CAMERA_H
#define BUILDER_CAMERA_H

#include "../object/camera.h"
#include "base_builder.h"

class BuilderCamera : public BaseBuilder {
public:
    BuilderCamera() = default;
    ~BuilderCamera() = default;

    void build() override;
    bool isBuild() const override;
    std::shared_ptr<Object> get();

private:
    std::shared_ptr<Camera> _camera_ptr;
};

#endif
