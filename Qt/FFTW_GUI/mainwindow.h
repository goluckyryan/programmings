#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include "qcustomplot.h"
#include "/usr/local/include/fftw3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void FouierForward();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot * plot;
    QCPColorMap *colorMap;

    QVector<double> *data;
    QVector<double> *fdataA;

    int nx, ny;

};

#endif // MAINWINDOW_H
