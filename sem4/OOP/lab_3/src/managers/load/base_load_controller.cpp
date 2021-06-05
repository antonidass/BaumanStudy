#include "../../../inc/managers/load/base_load_controller.h"

void BaseLoadController::setLoader(std::shared_ptr<BaseLoader> loader) {
    _loader = loader;
}