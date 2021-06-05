#ifndef MODEL_LOADER_FILE_H
#define MODEL_LOADER_FILE_H

#include "base_loader_figure.h"

class FigureLoaderFile : public BaseLoaderFigure {
public:
    FigureLoaderFile();
    explicit FigureLoaderFile(std::shared_ptr<std::ifstream> &file_in);
    ~FigureLoaderFile() override = default;

    void open(std::string &file_name) override;
    void close() override;
    std::shared_ptr<Object> load(std::shared_ptr<BuilderFigure> builder) override;

protected:
    std::shared_ptr<std::ifstream> _file;
};

#endif
