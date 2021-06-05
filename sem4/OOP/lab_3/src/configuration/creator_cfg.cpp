#include "../../inc/configuration/creator_cfg.h"
#include "../../inc/configuration/configuration.h"

std::shared_ptr<AbstractConfig> CreatorConfig::get_config(std::shared_ptr<std::string> source)
{
    if (nullptr == _config)
        create_instance(source);
    else if (source)
        _config->read_cfg(source);

    return _config;
}

void CreatorConfig::create_instance(std::shared_ptr<std::string> &source)
{
    static std::shared_ptr<AbstractConfig> conf(new Configuration(source));

    _config = conf;
}
