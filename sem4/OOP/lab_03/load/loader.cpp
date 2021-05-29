#include "loader.h"

std::shared_ptr<FigureComponent> fileLoader::loadFigure(std::shared_ptr<baseBuilder> builder) {
    builder->build();

    size_t points_count;
    this->file >> points_count;

    for (size_t i = 0; i < points_count; i++) {
        double x, y, z;
        this->file >> x >> y >> z;
        builder->buildPoint(x, y, z);
    }

    size_t links_count;
    this->file >> links_count;

    for (size_t i = 0; i < links_count; i++) {
        size_t pt1, pt2;
        this->file >> pt1 >> pt2;
        builder->buildLink(pt1, pt2);
    }

    return builder->get();
}

void fileLoader::fopen(std::string &fname) {
    this->file.open(fname);

    if (!this->file) {
        std::string message = "Error while open file.";
        throw fileException(message);
    }
}

void fileLoader::fclose() {
    try {
        this->file.close();
    } catch (std::ifstream::failure &error) {
        error.what();
    }
}

std::shared_ptr<FigureComponent> figureLoader::loadFigure(std::string &fname) {
    this->loader->fopen(fname);
    std::shared_ptr<FigureComponent> model(loader->loadFigure(this->builder));
    this->loader->fclose();

    return model;
}

