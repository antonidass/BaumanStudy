#include "timer.h"

void timer(int sec)
{
    QTime dieTime= QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
