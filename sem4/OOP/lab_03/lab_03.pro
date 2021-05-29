QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commands/command.cpp \
    gui/drawer.cpp \
    gui/factory.cpp \
    gui/mainwindow.cpp \
    facade/facade.cpp \
    load/abstract_loader.cpp \
    load/builder.cpp \
    load/loader.cpp \
    main.cpp \
    managers/managers.cpp \
    objects/component.cpp \
    objects/figure.cpp \
    objects/link.cpp \
    objects/point.cpp \
    scene/scene.cpp

HEADERS += \
    commands/command.h \
    errors/exceptions.h \
    facade/facade.h \
    gui/factory.h \
    gui/drawer.h \
    gui/mainwindow.h \
    load/abstract_loader.h \
    load/builder.h \
    load/loader.h \
    managers/managers.h \
    objects/component.h \
    objects/figure.h \
    objects/link.h \
    objects/point.h \
    scene/scene.h \
    vector/vector.h \
    vector/vector.hpp \
    vector/iterator.h \
    vector/iterator.hpp \
    visitor/visitor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
