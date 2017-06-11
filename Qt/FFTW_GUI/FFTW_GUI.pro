#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T20:51:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = FFTW_GUI
TEMPLATE = app

#unix:INCLUDEPATH += "/usr/local/include"
unix:LIBS += "/usr/local/lib/libfftw3.a"


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
