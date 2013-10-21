#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir mDir("~/test");

    qDebug() << mDir.exists();

    MainWindow w;
    w.show();
    
    return a.exec();
}
