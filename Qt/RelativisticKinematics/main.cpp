#include <QDebug>
#include "mainwindow.h"
#include <QApplication>
//#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   // QLabel *lab = new QLabel("mass [MeV/c <sup>2</sup>]");
    //lab->show();

    return a.exec();
}
