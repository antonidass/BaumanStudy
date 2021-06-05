#include "../../inc/builder/builder_figure.h"

void BuilderFigure::build() {
    _model_ptr = std::make_shared<FigureDetails>();
}

void BuilderFigure::buildPoint(const double &x, const double &y, const double &z) {
    Point tmp(x, y, z);
    _model_ptr->addPoint(tmp);
}

void BuilderFigure::buildLink(const size_t &dot1_num, const std::size_t dot2_num) {
    Link tmp(dot1_num, dot2_num);
    _model_ptr->addLink(tmp);
}

bool BuilderFigure::isBuild() const {
    return nullptr != _model_ptr;
}

std::shared_ptr<Object> BuilderFigure::get() {
    return std::make_shared<Figure>(Figure(_model_ptr));
}
