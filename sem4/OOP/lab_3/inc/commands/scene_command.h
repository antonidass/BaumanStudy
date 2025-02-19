#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include <memory>
#include "base_command.h"
#include "../drawer/abstract_drawer.h"

class DrawSceneCommand : public SceneBaseCommand {
public:
    DrawSceneCommand(std::shared_ptr<AbstractDrawer> drawer);
    virtual void exec() override;

private:
    std::shared_ptr<AbstractDrawer> _drawer;
};


class LoadSceneCommand : public SceneBaseCommand {
public:
    LoadSceneCommand(std::string file_name);
    virtual void exec() override;

private:
    std::string _file_name;
};

#endif
