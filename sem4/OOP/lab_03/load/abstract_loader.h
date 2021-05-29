#ifndef ABSTRACT_LOADER_H
#define ABSTRACT_LOADER_H

#include <memory>

#include "builder.h"
class baseLoader;


class abstractLoader {
public:
    abstractLoader() = default;
    ~abstractLoader() = default;

    virtual shared_ptr<FigureComponent> loadFigure(string &name) = 0;
    virtual void setLoader(shared_ptr<baseLoader> loader);

protected:
    shared_ptr<baseLoader> loader;
};



class figureLoader : public abstractLoader {
public:
    figureLoader(shared_ptr<baseLoader> loader);
    ~figureLoader() = default;

    virtual shared_ptr<FigureComponent> loadFigure(string &name) override;

private:
    shared_ptr<baseBuilder> builder;
    shared_ptr<baseLoader> loader;
};


#endif
