#include "../../inc/object/figure.h"

Figure::Figure(const Figure &model) {
    _figureDetails = model._figureDetails;
}

void Figure::accept(Visitor *visitor) {
    for (size_t i = 0; i < _figureDetails->getPoints().size(); i++) {
        _figureDetails->getPoints()[i].accept(visitor);
    }
}

bool Figure::isVisible() {
    return true;
}

bool Figure::isComposite() {
    return false;
}
