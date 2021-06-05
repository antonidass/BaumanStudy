#ifndef LOAD_MODEL_CONTROLLER_H
#define LOAD_MODEL_CONTROLLER_H

#include "base_load_controller.h"
#include "../../loader/base_loader_figure.h"
#include "../../loader/base_loader.h"
#include "../../builder/builder_figure.h"

class LoadModelController : public BaseLoadController {
public:
    explicit LoadModelController(std::shared_ptr<BaseLoaderFigure> loader);
    ~LoadModelController() = default;

    std::shared_ptr<Object> load(std::string &file_name);

private:
    std::shared_ptr<BuilderFigure> _builder;
    std::shared_ptr<BaseLoaderFigure> _loader;
};

#endif
