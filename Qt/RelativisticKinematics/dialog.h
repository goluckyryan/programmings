#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    double test;

    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setPlotRange(double xmin, double xmax, double ymin, double ymax);
    void plot(int id, QString name, QVector<double> x, QVector<double> y, QPen pen);
    void setAxisLabel(QString x, QString y);
    void setScatter(int id, bool visibleline);

private slots:

private:
    Ui::Dialog *ui;
    QCustomPlot *customPlot;

};

#endif // DIALOG_H
