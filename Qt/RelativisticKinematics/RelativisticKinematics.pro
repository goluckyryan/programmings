#-------------------------------------------------
#
# Project created by QtCreator 2016-08-27T00:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    nucleus.cpp

HEADERS  += mainwindow.h \
    nuclei_mass.h \
    constant.h \
    dialog.h \
    nucleus.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES += \
    mass12.txt

RESOURCES += \
    myresource.qrc
