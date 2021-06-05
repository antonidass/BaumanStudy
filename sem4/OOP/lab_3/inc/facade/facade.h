#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include "../commands/base_command.h"

class Facade {
public:
    void exec(BaseCommand &command);
};

#endif
