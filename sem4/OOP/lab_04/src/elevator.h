#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <deque>
#include <algorithm>
#include <QQueue>
#include <QDebug>
#include <QTimer>
#include "door.h"
#include "timer.h"
#include "control_panel.h"

class Elevator : public QObject {
    Q_OBJECT

    enum elevatorStatus { MOVING, STAND_OPEN, STAND_CLOSE};

public:
    Elevator(QObject *parent = nullptr);
    Door* getDoors();
    ControlPanel* getControlPanel();
    int getCurFloor();

signals:
    void targetIsReached();
    void newInfo(QString);

    void move();
    void stoped(int);

    void close_doors();

public slots:
    void moving();

    void goStandClose();
    void goStandOpen();
    void onTargetReceived(int);

private:
    elevatorStatus status;
    Door doors;
    ControlPanel control;
    QTimer liftWaitClose;
    QTimer newTargetTImer;
    QTimer timeMove;
    int time;

    int curFloor;
    int curDirection;
    int target;
};

#endif
