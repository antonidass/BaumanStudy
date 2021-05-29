#include "door.h"

Door::Door(QObject *parent) : QObject(parent) {
    status = OPENED;
    time = DOOR_TIME;

    doorOpenTimer.setSingleShot(true);
    doorCloseTimer.setSingleShot(true);

    connect(&doorOpenTimer, SIGNAL(timeout()), this, SLOT(open()));
    connect(&doorCloseTimer, SIGNAL(timeout()), this, SLOT(close()));
}


bool Door::isOpen() {
    return status == OPENED;
}


void Door::beginOpening() {
    if (!isOpen()) {
        status = OPENING;
        emit newInfo("Двери открываются");
        doorOpenTimer.start(time);
    }
}


void Door::beginClosing() {
    if (isOpen()) {
        status = CLOSING;
        emit newInfo("Двери закрываются");
        doorCloseTimer.start(time);
    }
}


void Door::close() {
    status = CLOSED;
    emit newInfo("Двери закрыты");
}


void Door::open() {
    status = OPENED;
    emit newInfo("Двери открыты");
}
