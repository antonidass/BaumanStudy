#include "../../inc/loader/loader_scene_file.h"
#include "../../inc/loader/loader_camera_file.h"
#include "../../inc/loader/loader_figure_file.h"
#include "../../inc/exceptions.h"

SceneLoaderFile::SceneLoaderFile() {
    _file = std::make_shared<std::ifstream>();
}

SceneLoaderFile::SceneLoaderFile(std::shared_ptr<std::ifstream> &file_in) {
    _file = file_in;
}

void SceneLoaderFile::open(std::string &file_name) {
    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
    _file->open(file_name);
    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
}


void SceneLoaderFile::close() {
    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
    _file->close();
}

std::shared_ptr<Scene> SceneLoaderFile::load(std::shared_ptr<BuilderScene> builder) {
    builder->build();
    loadModels(builder);
    loadCameras(builder);
    return builder->get();
}

void SceneLoaderFile::loadModels(std::shared_ptr<BuilderScene> builder) {
    int count_models;
    *_file >> count_models;

    auto model_builder = std::make_shared<BuilderFigure>();

    for (int i = 0; i < count_models; i++) {
        builder->buildFigure(FigureLoaderFile(_file).load(model_builder));
    }
}

void SceneLoaderFile::loadCameras(std::shared_ptr<BuilderScene> builder) {
    int count_cameras;
    *_file >> count_cameras;
    auto camera_builder = std::make_shared<BuilderCamera>();

    for (int i = 0; i < count_cameras; i++) {
        builder->buildCamera(std::dynamic_pointer_cast<Camera>(CameraLoaderFile(_file).load(camera_builder)));
    }
}
