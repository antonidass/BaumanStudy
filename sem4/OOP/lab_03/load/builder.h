#ifndef BUILDER_H
#define BUILDER_H

#include "../objects/component.h"
using namespace std;

class baseBuilder {
public:
    baseBuilder() = default;
    ~baseBuilder() = default;

    virtual bool isBuild() const = 0;
    virtual void build() = 0;
    virtual void buildPoint(const double &x, const double &y, const double &z) = 0;
    virtual void buildLink(const size_t &pt1, const size_t &pt2) = 0;

    virtual shared_ptr<FigureComponent> get() = 0;
};



class modelBuilder : public baseBuilder {
public:
    modelBuilder();
    ~modelBuilder() = default;

    virtual bool isBuild() const override;
    virtual void build() override;
    virtual void buildPoint(const double &x, const double &y, const double &z) override;
    virtual void buildLink(const size_t &pt1, const size_t &pt2) override;

    virtual shared_ptr<FigureComponent> get() override;

private:
    shared_ptr<FigureComponent> figure;
};

#endif // BUILDER_H
