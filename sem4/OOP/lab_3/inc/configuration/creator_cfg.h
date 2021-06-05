#ifndef CREATOR_CFG_H
#define CREATOR_CFG_H

#include <memory>
#include "abstract_cfg.h"

class CreatorConfig
{
public:
    std::shared_ptr<AbstractConfig> get_config(std::shared_ptr<std::string> source = nullptr);

private:
    void create_instance(std::shared_ptr<std::string> &source);

    std::shared_ptr<AbstractConfig> _config;
};

#endif
