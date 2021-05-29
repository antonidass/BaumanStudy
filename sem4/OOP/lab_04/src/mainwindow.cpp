#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Elevator");

    connect(elevator.getDoors(), SIGNAL(newInfo(QString)), this, SLOT(setInfo(QString)));
    connect(&elevator, SIGNAL(newInfo(QString)), this, SLOT(setInfo(QString)));
    connect(this, SIGNAL(addReq(int)), elevator.getControlPanel(), SLOT(addTarget(int)));

    connect(ui->floor1, SIGNAL(clicked(bool)), this, SLOT(onClickCab1()));
    connect(ui->floor2, SIGNAL(clicked(bool)), this, SLOT(onClickCab2()));
    connect(ui->floor3, SIGNAL(clicked(bool)), this, SLOT(onClickCab3()));
    connect(ui->floor4, SIGNAL(clicked(bool)), this, SLOT(onClickCab4()));
    connect(ui->floor5, SIGNAL(clicked(bool)), this, SLOT(onClickCab5()));
    connect(ui->callFrom1, SIGNAL(clicked(bool)), this, SLOT(onClickFrom1()));
    connect(ui->callFrom2, SIGNAL(clicked(bool)), this, SLOT(onClickFrom2()));
    connect(ui->callFrom3, SIGNAL(clicked(bool)), this, SLOT(onClickFrom3()));
    connect(ui->callFrom4, SIGNAL(clicked(bool)), this, SLOT(onClickFrom4()));
    connect(ui->callFrom5, SIGNAL(clicked(bool)), this, SLOT(onClickFrom5()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::stop() {
    QString info = "Лифт стоит на " + QString::number(elevator.getCurFloor()) + " этаже";
    ui->textBrowser->append(info);
}

void MainWindow::moving() {
    QString info = "Лифт на " + QString::number(elevator.getCurFloor()) + " этаже";
    ui->textBrowser->append(info);
}

void MainWindow::close() {
    QString info = "Двери закрыты";
    ui->textBrowser->append(info);
}

void MainWindow::open() {
    QString info = "Двери открыты";
    ui->textBrowser->append(info);
}

void MainWindow::startClosing() {
    QString info = "Двери закрываются";
    ui->textBrowser->append(info);
}

void MainWindow::startOpening() {
    QString info = "Двери открываются";
    ui->textBrowser->append(info);
}

void MainWindow::setInfo(QString info) {
    ui->textBrowser->append(info);
}

void MainWindow::onClickFrom1() {
    ui->textBrowser->append("Вызвали лифт на 1 этаже");
    emit addReq(1);
}

void MainWindow::onClickFrom2() {
    ui->textBrowser->append("Вызвали лифт на 2 этаже");
    emit addReq(2);
}

void MainWindow::onClickFrom3() {
    ui->textBrowser->append("Вызвали лифт на 3 этаже");
    emit addReq(3);
}

void MainWindow::onClickFrom4() {
    ui->textBrowser->append("Вызвали лифт на 4 этаже");
    emit addReq(4);
}

void MainWindow::onClickFrom5() {
    ui->textBrowser->append("Вызвали лифт на 5 этаже");
    emit addReq(5);
}

void MainWindow::onClickCab1() {
    ui->textBrowser->append("Нажали на кнопку 1 этажа в кабине");
    emit addReq(1);
}

void MainWindow::onClickCab2() {
    ui->textBrowser->append("Нажали на кнопку 2 этажа в кабине");
    emit addReq(2);
}

void MainWindow::onClickCab3() {
    ui->textBrowser->append("Нажали на кнопку 3 этажа в кабине");
    emit addReq(3);
}

void MainWindow::onClickCab4() {
    ui->textBrowser->append("Нажали на кнопку 4 этажа в кабине");
    emit addReq(4);
}

void MainWindow::onClickCab5() {
    ui->textBrowser->append("Нажали на кнопку 5 этажа в кабине");
    emit addReq(5);
}

