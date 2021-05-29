#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent) {
    status = STAND_OPEN;
    curFloor = 1;
    target = 1;
    curDirection = STAY;

    doors.beginOpening();

    liftWaitClose.setSingleShot(true);
    newTargetTImer.setSingleShot(true);

    time = CROSSING_TIME;
    timeMove.setSingleShot(true);

    connect(this, SIGNAL(targetIsReached()), this, SLOT(goStandOpen()));
    connect(&newTargetTImer, SIGNAL(timeout()), this, SLOT(goStandClose()));
    connect(this, SIGNAL(close_doors()), &doors, SLOT(beginClosing()));
    connect(&timeMove, SIGNAL(timeout()), this, SLOT(moving()));
    connect(this, SIGNAL(move()), this, SLOT(moving()));
    connect(this, SIGNAL(stoped(int)), &doors, SLOT(beginOpening()));
    connect(this, SIGNAL(stoped(int)), &control, SLOT(removeTarget(int)));
    connect(&control, SIGNAL(newTarget(int)), this, SLOT(onTargetReceived(int)));
    connect(&liftWaitClose, SIGNAL(timeout()), this, SLOT(moving()));
}



void Elevator::onTargetReceived(int i) {
    if (status == MOVING || status == STAND_CLOSE) {
        return;
    }

    target = i;

    if (target > curFloor) {
        curDirection = UP;
        emit move();
    }
    else if (target < curFloor) {
        curDirection = DOWN;
        emit move();
    }
    else if (target == curFloor) {
        emit targetIsReached();
    }
}


void Elevator::moving() {
    if (status == STAND_OPEN) {
        newTargetTImer.start(DOOR_TIME);
        liftWaitClose.start(WAIT_DOOR_TIME);
    } else {
        emit newInfo("Лифт на " + QString::number(curFloor) + " этаже");
        curFloor += curDirection;
        status = MOVING;

        if (target == curFloor) {
            emit targetIsReached();
        }
        else {
            timeMove.start(time);
        }
    }
}


void Elevator::goStandOpen() {
    status = STAND_OPEN;
    emit newInfo("Лифт стоит на " + QString::number(curFloor) + " этаже");
    curDirection = STAY;
    control.setDirection(curDirection);
    emit stoped(curFloor);
}


void Elevator::goStandClose() {
    status = STAND_CLOSE;
    emit close_doors();
}


Door* Elevator::getDoors() {
    return &doors;
}

ControlPanel* Elevator::getControlPanel() {
    return &control;
}

int Elevator::getCurFloor() {
    return curFloor;
}
