#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>

#include "../facade/facade.h"
#include "../commands/command.h"
#include "../errors/exceptions.h"
#include "ui_mainwindow.h"
#include "factory.h"
#include "drawer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    const int win_x = 988;
    const int win_y = 568;

    void setup_scene();

    void update_scene();

    void check_cam_exist();

    void check_models_exist();

private slots:
    void on_move_button_clicked();

    void on_scale_button_clicked();

    void on_turn_button_clicked();

    void on_load_button_clicked();

    void on_add_camera_clicked();

    void on_right_button_clicked();

    void on_up_button_clicked();

    void on_down_button_clicked();

    void on_left_button_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *_scene;
    shared_ptr<Facade> _facade;
    shared_ptr<baseDrawer> _drawer;
};
#endif
