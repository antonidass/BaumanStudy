#include "factory.h"

unique_ptr<baseDrawer> qtFactory::createGraphics() {
    return unique_ptr<baseDrawer> (new qtDrawer);
}
