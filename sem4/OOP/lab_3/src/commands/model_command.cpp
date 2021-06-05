#include "../../inc/commands/model_command.h"
#include "../../inc/managers/load/load_manager_creator.h"
#include "../../inc/managers/load/load_model_controller_creator.h"
#include "../../inc/managers/scene/scene_manager_creator.h"
#include "../../inc/managers/transform/transform_manager_creator.h"

MoveFigureCommand::MoveFigureCommand(const double &dx, const double &dy, const double &dz, const std::size_t model_num) :
    _dx(dx), _dy(dy), _dz(dz), _model_num(model_num) { }

void MoveFigureCommand::exec() {
    std::shared_ptr<Object> model = CreatorSceneManager().createManager()->getScene()->getFigures().at(_model_num);
    CreatorTransformManager().create_manager()->moveObject(model, _dx, _dy, _dz);
}

ScaleFigureCommand::ScaleFigureCommand(const double &kx, const double &ky, const double &kz, const std::size_t model_num) :
    _kx(kx), _ky(ky), _kz(kz), _model_num(model_num) { }

void ScaleFigureCommand::exec() {
    std::shared_ptr<Object> model = CreatorSceneManager().createManager()->getScene()->getFigures().at(_model_num);
    CreatorTransformManager().create_manager()->scaleObject(model, _kx, _ky, _kz);
}

RotateFigureCommand::RotateFigureCommand(const double &ox, const double &oy, const double &oz, const std::size_t model_num) :
        _ox(ox), _oy(oy), _oz(oz), _model_num(model_num) { }

void RotateFigureCommand::exec() {
    std::shared_ptr<Object> model = CreatorSceneManager().createManager()->getScene()->getFigures().at(_model_num);
    CreatorTransformManager().create_manager()->spinObject(model, _ox, _oy, _oz);
}

AddFigureCommand::AddFigureCommand(std::shared_ptr<Object> model) : _model(model) { }

void AddFigureCommand::exec() {
    CreatorSceneManager().createManager()->getScene()->addFigure(_model);
}

RemoveFigureCommand::RemoveFigureCommand(const std::size_t model_num) : _model_num(model_num) { }

void RemoveFigureCommand::exec() {
    CreatorSceneManager().createManager()->getScene()->removeFigure(_model_num);
}

CountFigureCommand::CountFigureCommand(const std::shared_ptr<std::size_t> &count) : _count(count) { }

void CountFigureCommand::exec() {
    (*_count) = CreatorSceneManager().createManager()->getScene()->getFigures().size();
}

#include <iostream>

LoadFigureCommand::LoadFigureCommand(std::string file_name) : _file_name(file_name) { }

void LoadFigureCommand::exec() {
    auto moderator = LoadModelControllerCreator().createController();
    auto manager = CreatorLoadManager().create_manager(moderator);
    auto model = manager->loadObject(_file_name);
    CreatorSceneManager().createManager()->getScene()->addFigure(model);
}
