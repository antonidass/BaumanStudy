#ifndef VISITOR_H
#define VISITOR_H

class CameraComponent;
class FigureComponent;
class Composite;

class Visitor {
public:
    Visitor() = default;
    ~Visitor() = default;

    virtual void visit(const CameraComponent &cam) = 0;
    virtual void visit(const FigureComponent &figureComp) = 0;
    virtual void visit(const Composite &composite) = 0;
};

#endif
