#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../object/object.h"

class Scene : public Object
{
public:
    Scene();
    ~Scene() override = default;

    std::vector<std::shared_ptr<Object>> get_models();
    std::vector<std::shared_ptr<Camera>> get_cameras();
    std::shared_ptr<Composite>           get_composite();

    void add_model    (const std::shared_ptr<Object> &model);
    void add_camera   (const std::shared_ptr<Camera> &camera);
    void remove_model (const std::size_t index);
    void remove_camera(const std::size_t index);

protected:
    void accept(std::shared_ptr<Visitor> visitor) override {};
    void transform(const Dot &move, const Dot &scale, const Dot &rotate) override {};

    std::vector<std::shared_ptr<Camera>> _cameras;
    std::shared_ptr<Composite> _models;
};

#endif
