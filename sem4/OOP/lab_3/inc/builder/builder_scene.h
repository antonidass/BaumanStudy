#ifndef BUILDER_SCENE_H
#define BUILDER_SCENE_H

#include "../scene/scene.h"
#include "base_builder.h"

class BuilderScene : public BaseBuilder {
public:
    BuilderScene() = default;
    ~BuilderScene() = default;

    void build() override;
    void buildFigure(const std::shared_ptr<Object> &object);
    void buildCamera(const std::shared_ptr<Camera> &camera);
    bool isBuild() const override;

    std::shared_ptr<Scene> get();

private:
    std::shared_ptr<Scene> _scene_ptr;
};

#endif
