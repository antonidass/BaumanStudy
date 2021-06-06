#ifndef LOAD_MODEL_CONTROLLER_H
#define LOAD_MODEL_CONTROLLER_H

#include "abstract_load_controller.h"
#include "../../loader/base_loader_model.h"
#include "../../loader/base_loader.h"
#include "../../builder/builder_model.h"

class LoadModelController : public AbstractLoadController
{
public:
    explicit LoadModelController(std::shared_ptr<BaseLoaderModel> loader);
    ~LoadModelController() = default;

    std::shared_ptr<Object> load(std::string &file_name) override;

private:
    std::shared_ptr<BuilderModel> _builder;
    std::shared_ptr<BaseLoaderModel> _loader;
};

#endif
