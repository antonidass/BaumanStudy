QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    check.cpp \
    draw.cpp \
    draw_qt.cpp \
    edge.cpp \
    event_handler.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    point.cpp \
    utils.cpp

HEADERS += \
    check.h \
    constants.h \
    draw.h \
    draw_qt.h \
    edge.h \
    event_handler.h \
    mainwindow.h \
    model.h \
    point.h \
    structures.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
