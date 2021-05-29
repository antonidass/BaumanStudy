#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <string>
#include "../facade/facade.h"
#include "../objects/component.h"


class baseCommand {
public:
    baseCommand() = default;
    virtual ~baseCommand() = default;
    virtual void execute(shared_ptr<Facade> &facade) = 0;
};


class loadFigure : public baseCommand {
public:
    loadFigure() = delete;
    loadFigure(const string &fileName);
    ~loadFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    string fileName;
};



class addFigure : public baseCommand {
public:
    addFigure() = delete;
    addFigure(const shared_ptr<Component> &figure);
    ~addFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    shared_ptr<Component> figure;
};



class moveFigure : public baseCommand {
public:
    moveFigure() = delete;
    moveFigure(const double &dx, const double &dy, const double &dz, const size_t &num);
    ~moveFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    double dx, dy, dz;
    size_t num;
};



class scaleFigure : public baseCommand {
public:
    scaleFigure() = delete;
    scaleFigure(const double &kx, const double &ky, const double &kz, const size_t &num);
    ~scaleFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    double kx, ky, kz;
    size_t num;
};



class rotateFigure : public baseCommand {
public:
    rotateFigure() = delete;
    rotateFigure(const double &ox, const double &oy, const double &oz, const size_t &num);
    ~rotateFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    double ox, oy, oz;
    size_t num;
};



class transformFigure : public baseCommand {
public:
    transformFigure() = delete;
    transformFigure(const size_t &num, const Point &move, const Point &scale, const Point &rotate);
    ~transformFigure() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    size_t num;
    Point move, scale, rotate;
};



class addCamera : public baseCommand {
public:
    addCamera() = delete;
    addCamera(const double x, const double y, const double z);
    ~addCamera() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    double xPos, yPos, zPos;
};




class moveCamera : public baseCommand {
public:
    moveCamera() = delete;
    moveCamera(const size_t &num, const double &ox, const double &oy);
    ~moveCamera() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    size_t num;
    double ox, oy;
};



class drawScene : public baseCommand {
public:
    drawScene() = delete;
    drawScene(shared_ptr<baseDrawer> drawer);
    ~drawScene() = default;
    virtual void execute(shared_ptr<Facade> &facade) override;

private:
    shared_ptr<baseDrawer> drawer;
};


#endif
