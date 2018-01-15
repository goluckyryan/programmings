#ifndef KNOCKOUT_H
#define KNOCKOUT_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class KnockoutDialog;
}

class KnockoutDialog : public QDialog
{
    Q_OBJECT

public:
    double test;

    explicit KnockoutDialog(QWidget *parent = 0);
    ~KnockoutDialog();
    void setPlotRange(double xmin, double xmax, double ymin, double ymax);
    void plot(int id, QString name, QVector<double> x, QVector<double> y, QPen pen);
    void setAxisLabel(QString x, QString y);
    void setScatter(int id, bool visibleline);

private slots:

private:
    Ui::KnockoutDialog *ui;
    QCustomPlot *customPlot;

};

#endif // KNOCKOUT_H
