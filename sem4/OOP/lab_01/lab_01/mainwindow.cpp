#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "event_handler.h"
#include "constants.h"
#include "model.h"
#include "check.h"


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
    eventT event;
    event.type = FREE_MODEL;
    eventHandler(event);

    delete ui;
}


eventT MainWindow::makeDrawEvent() {
    eventT event;
    event.type = DRAW_MODEL;

    canvasT canvas;
    canvas.scene = scene;

    event.canvas = canvas;

    return event;
}


void MainWindow::makeErrorMessage(const char msg[]) {
    QMessageBox::about(this, ERR_TITLE, msg);
}


int MainWindow::handleRepsond(const int &check) {
    if (!check) {
        return check;
    }

    char error[WORD_LEN];
    handleError(check, error);
    makeErrorMessage(error);

    return check;
}


void MainWindow::on_LoadBut_clicked()
{
    eventT event;
    event.type = LOAD_MODEL;
    strcpy(event.fileName, FILE_NAME);

    int check = eventHandler(event);

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
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

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
        return;
    }
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

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
        return;
    }
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

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
        return;
    }
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

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
        return;
    }
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

    if (handleRepsond(check)) {
        return;
    }

    eventT drawEvent = makeDrawEvent();
    check = eventHandler(drawEvent);

    if (handleRepsond(check)) {
        return;
    }
}
