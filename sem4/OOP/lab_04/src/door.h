#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "timer.h"
#include "constants.h"

class Door : public QObject {
    Q_OBJECT


public:
    explicit Door(QObject *parent = nullptr);
    enum doorStatus { OPENED, CLOSED, OPENING, CLOSING };

signals:
    void closed();
    void newInfo(QString);

public slots:
    void beginOpening();
    void beginClosing();

private slots:
    void open();
    void close();
    bool isOpen();



private:
    doorStatus status;
    QTimer doorOpenTimer;
    QTimer doorCloseTimer;
    int time;
};

#endif
