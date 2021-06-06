#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include <memory>

#include "../base_manager.h"
#include "../../model/model.h"
#include "abstract_load_controller.h"

class LoadManager : BaseManager
{
public:
    LoadManager();
    LoadManager(const LoadManager &manager) = delete;
    LoadManager &operator = (const LoadManager &manager) = delete;

    ~LoadManager() = default;

    virtual std::shared_ptr<Object> load(std::string &name);
    virtual void set_loader(std::shared_ptr<AbstractLoadController> loader);

private:
    std::shared_ptr<AbstractLoadController> _loader;
};

#endif
