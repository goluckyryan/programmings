#-------------------------------------------------
#
# Project created by QtCreator 2016-08-27T00:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Qt_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    nucleus.cpp \
    qcustomplot.cpp \
    matrix.cpp \
    fourvector.cpp \
    lorentzian.cpp

HEADERS  += mainwindow.h \
    constant.h \
    dialog.h \
    nucleus.h \
    qcustomplot.h \
    matrix.h \
    fourvector.h \
    lorentzian.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES += \
    mass12.txt

RESOURCES += \
    myresource.qrc
