#include "../../inc/commands/camera_command.h"
#include "../../inc/camera/camera.h"
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
    
void AddCameraCommand::exec()
{
    Dot camera_place(_x, _y, _z);

    std::shared_ptr<Camera> camera(new Camera);

    camera->transform(camera_place, camera_place, camera_place);

    auto scene_manager = CreatorSceneManager().create_manager();
    scene_manager->get_scene()->add_camera(camera);
    scene_manager->set_camera(scene_manager->get_scene()->get_cameras().size() - 1);
};

void RemoveCameraCommand::exec()
{
    CreatorSceneManager().create_manager()->get_scene()->remove_camera(_camera_num);
}

void MoveCameraCommand::exec()
{
    Dot move(_dx, _dy, 0);

    auto viewer = CreatorSceneManager().create_manager()->get_scene()->get_cameras().at(_camera_num);

    CreatorTransformManager().create_manager()->transform_object(viewer, move, move, move);
}

void SetCameraCommand::exec()
{
    CreatorSceneManager().create_manager()->set_camera(_camera_num);
}

void CountCameraCommand::exec()
{
    (*_count) = CreatorSceneManager().create_manager()->get_scene()->get_cameras().size();
}
