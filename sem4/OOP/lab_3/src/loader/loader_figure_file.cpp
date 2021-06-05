#include "../../inc/loader/loader_figure_file.h"
#include "../../inc/exceptions.h"
#include "../../inc/builder/builder_figure.h"

FigureLoaderFile::FigureLoaderFile() {
    _file = std::make_shared<std::ifstream>();
}

FigureLoaderFile::FigureLoaderFile(std::shared_ptr<std::ifstream> &file_in) {
    _file = file_in;
}

void FigureLoaderFile::open(std::string &file_name){
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


void FigureLoaderFile::close() {
    if (!_file) {
        std::string msg = "Error : File open";
        throw SourceException(msg);
    }
    _file->close();
}

std::shared_ptr<Object> FigureLoaderFile::load(std::shared_ptr<BuilderFigure> builder) {
    builder->build();
    int count_dots;
    *_file >> count_dots;
    for (int i = 0; i < count_dots; i++) {
        double x, y, z;
        *_file >> x >> y >> z;
        builder->buildPoint(x, y, z);
    }

    int count_links;
    *_file >> count_links;

    for (int i = 0; i < count_links; i++) {
        int dot1_num, dot2_num;
        *_file >> dot1_num >> dot2_num;
        builder->buildLink(dot1_num, dot2_num);
    }
    return builder->get();
}
