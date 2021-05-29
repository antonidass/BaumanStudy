#include "abstract_loader.h"

void abstractLoader::setLoader(shared_ptr<baseLoader> loader) {
    this->loader = loader;
}

figureLoader::figureLoader(shared_ptr<baseLoader> loader) : builder (new modelBuilder), loader(loader) {};
