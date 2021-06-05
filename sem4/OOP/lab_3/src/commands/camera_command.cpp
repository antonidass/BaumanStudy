#include "../../inc/commands/camera_command.h"
#include "../../inc/object/camera.h"
#include "../../inc/managers/scene/scene_manager_creator.h"
#include "../../inc/managers/transform/transform_manager_creator.h"

AddCameraCommand::AddCameraCommand(const double x, const double y, const double z)
    : _x(x), _y(y), _z(z) {}

RemoveCameraCommand::RemoveCameraCommand(const size_t &camera_num) : 
    _camera_num(camera_num) { }

MoveCameraCommand::MoveCameraCommand(const size_t &camera_num, const double &dx, const double &dy) :
    _camera_num(camera_num), _dx(dx), _dy(dy) { }

SetCameraCommand::SetCameraCommand(const size_t &camera_num) : 
    _camera_num(camera_num) { }

CountCameraCommand::CountCameraCommand(const std::shared_ptr<size_t> &count) : 
    _count(count) { }
    
void AddCameraCommand::exec() {
    Point camera_place(_x, _y, _z);
    std::shared_ptr<Camera> camera(new Camera);
//    camera->transform(camera_place, camera_place, camera_place);

    MoveVisitor moveVisitor(_x, _y, _z);
    std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(camera);
    moveVisitor.visit(cam);

    auto scene_manager = CreatorSceneManager().createManager();
    scene_manager->getScene()->addCamera(camera);
    scene_manager->setCamera(scene_manager->getScene()->getCameras().size() - 1);
};

void RemoveCameraCommand::exec() {
    CreatorSceneManager().createManager()->getScene()->removeCamera(_camera_num);
}

void MoveCameraCommand::exec() {
    auto viewer = CreatorSceneManager().createManager()->getScene()->getCameras().at(_camera_num);
    CreatorTransformManager().create_manager()->moveObject(viewer, _dx, _dy, 0);
}

void SetCameraCommand::exec() {
    CreatorSceneManager().createManager()->setCamera(_camera_num);
}

void CountCameraCommand::exec() {
    (*_count) = CreatorSceneManager().createManager()->getScene()->getCameras().size();
}
