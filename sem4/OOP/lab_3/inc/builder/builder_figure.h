#ifndef BUILDER_MODEL_H
#define BUILDER_MODEL_H

#include "../model/figure_details.h"
#include "../object/figure.h"
#include "base_builder.h"

class BuilderFigure : public BaseBuilder {
public:
    BuilderFigure()  = default;
    ~BuilderFigure() = default;

    void build() override;
    void buildPoint(const double &x, const double &y, const double &z);
    void buildLink(const std::size_t &dot1_num, const std::size_t dot2_num);

    bool isBuild() const override;
    std::shared_ptr<Object> get();

private:
    std::shared_ptr<FigureDetails> _model_ptr;
};

#endif
