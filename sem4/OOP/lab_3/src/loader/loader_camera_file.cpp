#include "../../inc/loader/loader_camera_file.h"
#include "../../inc/exceptions.h"

CameraLoaderFile::CameraLoaderFile() {
    _file = std::make_shared<std::ifstream>();
}

CameraLoaderFile::CameraLoaderFile(std::shared_ptr<std::ifstream> &file_in) {
    _file = file_in;
}

void CameraLoaderFile::open(std::string &file_name) {
    if (!_file)
    {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }

    _file->open(file_name);

    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
}

void CameraLoaderFile::close() {
    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
    _file->close();
}

std::shared_ptr<Object> CameraLoaderFile::load(std::shared_ptr<BuilderCamera> builder) {
    builder->build();
    double x, y, z;
    *_file >> x >> y >> z;
    return builder->get();
}
