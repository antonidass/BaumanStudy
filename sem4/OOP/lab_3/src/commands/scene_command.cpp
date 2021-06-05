#include "../../inc/commands/scene_command.h"
#include "../../inc/managers/draw/draw_manager_creator.h"
#include "../../inc/managers/load/load_manager_creator.h"
#include "../../inc/managers/scene/scene_manager_creator.h"
#include "../../inc/managers/load/load_scene_controller_creator.h"

DrawSceneCommand::DrawSceneCommand(std::shared_ptr<AbstractDrawer> drawer) : _drawer(drawer) { }

void DrawSceneCommand::exec() {
    auto draw_manager = CreatorDrawManager().createManager();
    auto scene_manager = CreatorSceneManager().createManager();
    auto camera = scene_manager->getCamera();

    _drawer->clearScene();
    draw_manager->setDrawer(_drawer);
    draw_manager->setCamera(camera);
    draw_manager->setScene(scene_manager->getScene());
    draw_manager->execute();
}

LoadSceneCommand::LoadSceneCommand(std::string file_name) : _file_name(file_name) { }

void LoadSceneCommand::exec() {
    auto moderator = LoadSceneControllerCreator().createController();
    auto manager = CreatorLoadManager().create_manager(moderator);
    auto scene = std::dynamic_pointer_cast<Scene>(manager->loadScene(_file_name));

    CreatorSceneManager().createManager()->setScene(scene);
}