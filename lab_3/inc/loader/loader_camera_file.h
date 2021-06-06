#ifndef LOADER_CAMERA_FILE_H
#define LOADER_CAMERA_FILE_H

#include "base_loader_camera.h"

class CameraLoaderFile : public BaseLoaderCamera
{
public:
    CameraLoaderFile();
    explicit CameraLoaderFile(std::shared_ptr<std::ifstream> &file_in);
    ~CameraLoaderFile() override = default;

    void open(std::string &file_name) override;
    void close() override;

    std::shared_ptr<Object> load(std::shared_ptr<BuilderCamera> builder) override;

protected:
    std::shared_ptr<std::ifstream> _file;
};

#endif
