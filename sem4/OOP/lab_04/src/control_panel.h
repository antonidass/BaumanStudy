#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QObject>
#include <QWidget>
#include <QDebug>

#include "constants.h"

class ControlPanel : public QWidget {
    Q_OBJECT
    enum Status { HAS_TARGET, NO_TARGET };

public:
    ControlPanel(QWidget *parent = nullptr);
    void setDirection(int);
    int getCurTarg();
    void setCurTarg(int);
    void getNewTarget();

public slots:
    void removeTarget(int);
    void addTarget(int);

signals:
    void newTarget(int);

private slots:
    bool next_target(int &floor);
private:
    bool targets[FLOOR_NUM];
    int maxFloor;
    int minFloor;
    int curFloor;
    int direction;
    int target;
    Status status;
};

#endif
