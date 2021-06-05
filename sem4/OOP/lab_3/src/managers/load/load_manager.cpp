#include "../../../inc/managers/load/load_manager.h"
#include "../../../inc/managers/load/load_scene_controller_creator.h"
#include "../../../inc/managers/load/load_model_controller.h"
#include "../../../inc/managers/load/load_model_controller_creator.h"

LoadManager::LoadManager() {
    _loaderScene = LoadSceneControllerCreator().createController();
    _loaderFigure = LoadModelControllerCreator().createController();
}

std::shared_ptr<Scene> LoadManager::loadScene(std::string &name) {
    return _loaderScene->load(name);
}

std::shared_ptr<Object> LoadManager::loadObject(std::string &name) {
    return _loaderFigure->load(name);
}


void LoadManager::set_loader(std::shared_ptr<LoadSceneController> loader) {
    _loaderScene = loader;
}

void LoadManager::set_loader(std::shared_ptr<LoadModelController> loader) {
    _loaderFigure = loader;
}