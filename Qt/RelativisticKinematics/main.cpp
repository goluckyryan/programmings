#include <QDebug>
#include "mainwindow.h"
#include <QApplication>
//#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setGeometry(0,0, w.geometry().width(), w.geometry().height());
    w.show();

    return a.exec();
}
