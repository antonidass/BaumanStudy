#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "base_command.h"
#include <memory>
#include <cstddef>

class AddCameraCommand : public CameraBaseCommand {
public:
    AddCameraCommand(const double x, const double y, const double z);
    virtual void exec() override;

private:
    double _x, _y, _z;
};


class RemoveCameraCommand : public CameraBaseCommand {
public:
    RemoveCameraCommand(const std::size_t &camera_num);
    virtual void exec() override;

private:
    std::size_t _camera_num;
};


class MoveCameraCommand : public CameraBaseCommand {
public:
    MoveCameraCommand(const std::size_t &camera_num, const double &dx, const double &dy);
    virtual void exec() override;
private:
    double _dx, _dy;
    std::size_t _camera_num;
};


class SetCameraCommand : public CameraBaseCommand {
public:
    SetCameraCommand(const std::size_t &camera_num);
    virtual void exec() override;

private:
    std::size_t _camera_num;
};


class CountCameraCommand : public CameraBaseCommand {
public:
    CountCameraCommand(const std::shared_ptr<size_t> &count);
    virtual void exec() override;

private:
    std::shared_ptr<size_t> _count;
};

#endif
