#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include <cstddef>
#include <memory>

#include "base_command.h"
#include "../object/object.h"
#include "../model/point.h"

class MoveFigureCommand : public FigureCommandBase {
public:
    MoveFigureCommand(const double &dx, const double &dy, const double &dz, const std::size_t model_num);
    virtual void exec() override;

private:
    std::size_t _model_num;
    double _dx, _dy, _dz;
};


class ScaleFigureCommand : public FigureCommandBase {
public:
    ScaleFigureCommand(const double &kx, const double &ky, const double &kz, const std::size_t model_num);
    virtual void exec() override;

private:
    std::size_t _model_num;
    double _kx, _ky, _kz;
};


class RotateFigureCommand : public FigureCommandBase {
public:
    RotateFigureCommand(const double &ox, const double &oy, const double &oz, const std::size_t model_num);
    virtual void exec() override;

private:
    std::size_t _model_num;
    double _ox, _oy, _oz;
};


class TransformFigureCommand : public FigureCommandBase {
public:
    TransformFigureCommand(const Point &move, const Point &scale, const Point &spin, const std::size_t model_num);
    virtual void exec() override;

private:
    std::size_t _model_num;
    Point _move, _scale, _rotate;
};

class AddFigureCommand : public FigureCommandBase {
public:
    AddFigureCommand(std::shared_ptr<Object> model);
    virtual void exec() override;

private:
    std::shared_ptr<Object> _model;
};


class RemoveFigureCommand : public FigureCommandBase {
public:
    RemoveFigureCommand(std::size_t model_num);
    virtual void exec() override;

private:
    std::size_t _model_num;
};


class CountFigureCommand : public FigureCommandBase {
public:
    CountFigureCommand(const std::shared_ptr<size_t> &count);
    virtual void exec() override;

private:
    std::shared_ptr<size_t> _count;
};


class LoadFigureCommand : public FigureCommandBase {
public:
    LoadFigureCommand(std::string file_name);
    virtual void exec() override;

private:
    std::string _file_name;
};

#endif
