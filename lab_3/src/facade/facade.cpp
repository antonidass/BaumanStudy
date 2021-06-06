#include "../../inc/facade/facade.h"

void Facade::exec(BaseCommand &command)
{
    command.exec();
}
