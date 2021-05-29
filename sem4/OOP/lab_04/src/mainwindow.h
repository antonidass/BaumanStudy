#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include <iostream>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Elevator elevator;

signals:
    void addReq(int);

private slots:
    void onClickFrom1();
    void onClickFrom2();
    void onClickFrom3();
    void onClickFrom4();
    void onClickFrom5();
    void onClickCab1();
    void onClickCab2();
    void onClickCab3();
    void onClickCab4();
    void onClickCab5();
    void setInfo(QString info);
    void close();
    void open();
    void startClosing();
    void startOpening();
    void stop();
    void moving();
};

#endif // MAINWINDOW_H
