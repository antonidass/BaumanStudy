#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "event_handler.h"
#include "constants.h"
#include "model.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_WIDHT, SCENE_HEIGHT);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makeDrawEvent() {
    eventT event;
    event.type = DRAW_MODEL;
    event.scene = scene;

    eventHandler(event);
}

void MainWindow::makeClearDataEvent() {
    eventT event;
    event.type = FREE_MODEL;

    eventHandler(event);
}


void MainWindow::makeErrorMessage(const char msg[]) {
    QMessageBox::about(this, ERR_TITLE, msg);
}


int MainWindow::checkError(const int &check) {
    if (check == ERR_ALLOC_MODEL) {
        makeErrorMessage(ERR_ALLOC_MSG);
    }
    else if (check == ERR_EMPTY_MODEL) {
        makeErrorMessage(ERR_EMPTY_MODEL_MSG);
    }
    else if (check == ERR_FILE_READ_INT) {
        makeErrorMessage(ERR_FILE_READ_INT_MSG);
    }
    else if (check == ERR_FILE_READ_POINT) {
        makeErrorMessage(ERR_FILE_READ_POINT_MSG);
    }
    else if (check == ERR_FILE_READ_EDGE_CONNECTION) {
        makeErrorMessage(ERR_FILE_READ_EDGE_MSG);
    }
    else if (check == ERR_SCALE_COEFF) {
        makeErrorMessage(ERR_SCALE_COEFF_MSG);
    }

    if (check != OK) {
        makeClearDataEvent();
    }

    return check;
}



void MainWindow::on_LoadBut_clicked()
{
    FILE *file = fopen("../lab_01/res/cube.txt", "r");

    if (!file) {
        makeErrorMessage(ERR_OPEN_MSG);
        return;
    }

    eventT event;
    event.type = LOAD_MODEL;
    event.file = file;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();

    if (fclose(file)) {
        makeErrorMessage(ERR_CLOSE_FILE_MSG);
        return;
    }
}


void MainWindow::on_moveBtn_clicked()
{
    double dx = ui->dxArea->toPlainText().toDouble();
    double dy = ui->dyArea->toPlainText().toDouble();
    double dz = ui->dzArea->toPlainText().toDouble();

    eventT event;
    event.type = MOVE_MODEL;
    event.move.dx = dx;
    event.move.dy = dy;
    event.move.dz = dz;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();
}


void MainWindow::on_rotateX_clicked()
{
    double rx = ui->rxArea->toPlainText().toDouble();

    eventT event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = rx;
    event.rotate.angle_y = 0.0;
    event.rotate.angle_z = 0.0;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();
}


void MainWindow::on_rotateY_clicked()
{
    double ry = ui->ryArea->toPlainText().toDouble();

    eventT event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = 0.0;
    event.rotate.angle_y = ry;
    event.rotate.angle_z = 0.0;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();
}

void MainWindow::on_rotateZ_clicked()
{
    double rz = ui->rzArea->toPlainText().toDouble();

    eventT event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = 0.0;
    event.rotate.angle_y = 0.0;
    event.rotate.angle_z = rz;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();
}

void MainWindow::on_scaleBtn_clicked()
{
    double kx = ui->scaleX->toPlainText().toDouble();
    double ky = ui->scaleY->toPlainText().toDouble();
    double kz = ui->scaleZ->toPlainText().toDouble();

    eventT event;
    event.type = SCALE_MODEL;
    event.scale.kx = kx;
    event.scale.ky = ky;
    event.scale.kz = kz;

    int check = eventHandler(event);

    if (checkError(check) != OK) {
        return;
    }

    makeDrawEvent();
}
