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
    nucleus.cpp \
    qcustomplot.cpp \
    matrix.cpp \
    fourvector.cpp \
    lorentzian.cpp \
    knockoutdialog.cpp

HEADERS  += mainwindow.h \
    constant.h \
    nucleus.h \
    qcustomplot.h \
    matrix.h \
    fourvector.h \
    lorentzian.h \
    knockoutdialog.h

FORMS    += mainwindow.ui \
    knockoutdialog.ui

DISTFILES += \
    mass12.txt

RESOURCES += \
    myresource.qrc
