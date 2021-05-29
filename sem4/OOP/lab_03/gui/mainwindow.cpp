#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _facade(nullptr) {
    ui->setupUi(this);
    this->setup_scene();
    this->_facade = std::make_shared<Facade>();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::check_cam_exist() {
    if (!this->_facade->camsCount()) {
        std::string message = "No camera found.";
        throw cameraException(message);
    }
}

void MainWindow::check_models_exist() {
    if (!this->_facade->figuresCount()) {
        std::string message = "No models found.";
        throw figureException(message);
    }
}

void MainWindow::on_move_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру");
        return;
    }

    moveFigure move_command(ui->dx_box->value(), ui->dy_box->value(), ui->dz_box->value(), 1);
    move_command.execute(_facade);
    update_scene();
}

void MainWindow::on_scale_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру");
        return;
    }

    scaleFigure scale_command(ui->kx_box->value(), ui->ky_box->value(), ui->kz_box->value(), 1);
    scale_command.execute(_facade);
    update_scene();
}

void MainWindow::on_turn_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Для начала нужно загрузить хотя бы одну камеру");
        return;
    }

    rotateFigure turn_command(ui->ox_box->value(), ui->ox_box->value(), ui->ox_box->value(), 1);
    turn_command.execute(_facade);
    update_scene();
}

void MainWindow::on_load_button_clicked() {
    try {
        check_cam_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Прежде чем добавлять модель, добавьте хотя бы одну камеру.");
        return;
    }

    loadFigure load_command("/home/akrik/BaumanStudy/sem4/OOP/lab_03/data/model.csv");

    try {
        load_command.execute(_facade);
    } catch (const fileException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Что-то не так пошло при загрузке файла...");
        return;
    }

    update_scene();
}

void MainWindow::setup_scene() {
    this->_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->_scene->setSceneRect(0, 0, win_x, win_y);

    std::shared_ptr<abstractFactory> factory(new qtFactory);
    std::shared_ptr<baseDrawer> drawer(new qtDrawer(this->_scene));
    this->_drawer = drawer;
}

void MainWindow::update_scene() {
    drawScene draw_command(this->_drawer);
    draw_command.execute(_facade);
}

void MainWindow::on_add_camera_clicked() {
    addCamera camera_command(win_x / 2, win_y / 2, 0);
    camera_command.execute(_facade);
}

void MainWindow::on_right_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    moveCamera camera_command(1, 10, 0);
    camera_command.execute(_facade);
    update_scene();
}

void MainWindow::on_up_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    moveCamera camera_command(1, 0, 10);
    camera_command.execute(_facade);
    update_scene();
}

void MainWindow::on_down_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    moveCamera camera_command(1, 0, -10);
    camera_command.execute(_facade);
    update_scene();
}

void MainWindow::on_left_button_clicked() {
    try {
        check_cam_exist();
        check_models_exist();
    } catch (const cameraException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const figureException &error) {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }

    moveCamera camera_command(1, -10, 0);
    camera_command.execute(_facade);
    update_scene();
}
