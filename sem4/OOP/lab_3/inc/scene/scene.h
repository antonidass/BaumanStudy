#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../object/object.h"

class Scene {
public:
    Scene();
    ~Scene() = default;

    std::vector<std::shared_ptr<Object>> getFigures();
    std::vector<std::shared_ptr<Camera>> getCameras();
    std::shared_ptr<Composite> getComposite();

    void addFigure (const std::shared_ptr<Object> &figure);
    void addCamera (const std::shared_ptr<Camera> &camera);
    void removeFigure (const std::size_t index);
    void removeCamera (const std::size_t index);

protected:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::shared_ptr<Composite> _figures;
};

#endif
