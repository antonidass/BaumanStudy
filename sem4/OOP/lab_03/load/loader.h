#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <fstream>

#include "builder.h"
#include "../errors/exceptions.h"
#include "../objects/component.h"
#include "abstract_loader.h"


class baseLoader {
public:
    baseLoader() = default;
    virtual ~baseLoader() = default;

    virtual shared_ptr<FigureComponent> loadFigure(shared_ptr<baseBuilder> builder) = 0;
    virtual void fopen(string &fname) = 0;
    virtual void fclose() = 0;
};



class fileLoader : public baseLoader {
public:
    fileLoader() = default;
    virtual ~fileLoader() = default;

    virtual shared_ptr<FigureComponent> loadFigure(shared_ptr<baseBuilder> builder) override;
    virtual void fopen(string &fname) override;
    virtual void fclose() override;

protected:
    ifstream file;
};


#endif
