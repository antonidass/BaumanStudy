#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <memory>
#include <libconfig.h++>

#include "abstract_cfg.h"
#include "../drawer/abstract_drawer.h"

#define CFG_FILE "/home/akrik/Рабочий стол/lab_3/data/config.cfg"

class Configuration : public AbstractConfig {
public:
    explicit Configuration(std::shared_ptr<std::string> &source);
    void read_cfg(std::shared_ptr<std::string> source = nullptr) override;

    AbstractConfig::frames get_frame() override;
    AbstractConfig::sources get_load_source() override;

private:
    std::shared_ptr<libconfig::Config> _cfg;
};

#endif
