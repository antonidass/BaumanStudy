#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <string>

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual void exec() = 0;
};


class CameraBaseCommand : public BaseCommand { };

class SceneBaseCommand : public BaseCommand { };

class ModelBaseCommand : public BaseCommand { };

#endif
