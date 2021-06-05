#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "../../object/object.h"
#include "../../visitor/transform_visitor.h"

class TransformManager {
public:
    TransformManager() = default;
    TransformManager(const TransformManager &manager) = delete;
    TransformManager &operator = (const TransformManager &manager) = delete;
    ~TransformManager() = default;

    static void moveObject(const std::shared_ptr<Object> &object, const double &dx, const double &dy, const double &dz);
    static void scaleObject(const std::shared_ptr<Object> &object, const double &kx, const double &ky, const double &kz);
    static void spinObject(const std::shared_ptr<Object> &object, const double &ox, const double &oy, const double &oz);
};

#endif //TRANSFORM_MANAGER_H
