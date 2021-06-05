#ifndef LOADER_SCENE_FILE_H
#define LOADER_SCENE_FILE_H

#include "base_loader_scene.h"

class SceneLoaderFile : public BaseLoaderScene {
public:
    SceneLoaderFile();
    explicit SceneLoaderFile(std::shared_ptr<std::ifstream> &file_in);
    ~SceneLoaderFile() override = default;

    void open(std::string &file_name) override;
    void close() override;
    std::shared_ptr<Scene> load(std::shared_ptr<BuilderScene> builder) override;

protected:
    void loadModels(std::shared_ptr<BuilderScene> builder) override;
    void loadCameras(std::shared_ptr<BuilderScene> builder) override;

    std::shared_ptr<std::ifstream> _file;
};

#endif
