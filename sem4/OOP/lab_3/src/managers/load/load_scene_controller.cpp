#include "../../../inc/managers/load/load_scene_controller.h"
#include "../../../inc/exceptions.h"

LoadSceneController::LoadSceneController(std::shared_ptr<BaseLoaderScene> loader) : _builder(new BuilderScene) {
    _loader = loader;
}

std::shared_ptr<Scene> LoadSceneController::load(std::string &file_name) {
    try {
        _loader->open(file_name);
    }
    catch (SourceException &error) {
        std::string msg = "Error : Open file";
        throw SourceException(msg);
    }
    std::shared_ptr<Scene> scene;
    try {
        scene = _loader->load(_builder);
    }
    catch (std::exception &error) {
        std::string msg = "Error : Read model";
        throw SourceException(msg);
    }
    _loader->close();
    return scene;
}
