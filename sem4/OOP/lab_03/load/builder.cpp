#include "builder.h"

modelBuilder::modelBuilder() : figure(nullptr) {}

bool modelBuilder::isBuild() const {
    return this->figure != nullptr;
}

void modelBuilder::build() {
    this->figure = std::make_shared<FigureComponent>();
}

void modelBuilder::buildPoint(const double &x, const double &y, const double &z) {
    if (!isBuild()) {
        qDebug() << "point fail";
    }

    Point pt_obj(x, y, z);
    this->figure->addPoint(pt_obj);
}

void modelBuilder::buildLink(const size_t &pt1, const size_t &pt2) {
    if (!isBuild()) {
        qDebug() << "link fail";
    }

    Link link_obj(pt1, pt2);
    this->figure->addLink(link_obj);
}

std::shared_ptr<FigureComponent> modelBuilder::get() {
    return figure;
}
