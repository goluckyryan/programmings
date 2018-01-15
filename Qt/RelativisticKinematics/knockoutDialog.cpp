#include "knockoutdialog.h"
#include "ui_knockoutdialog.h"

KnockoutDialog::KnockoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KnockoutDialog)
{
    ui->setupUi(this);

    test = 10.1;

    customPlot  = ui->customPlot;
    customPlot->addGraph();

    customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    // create graph and assign data to it:


    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = sin(x[i]); //
    }

    plot(0, "sin", x, y, QPen(Qt::blue));
    setPlotRange(-1,1, -1, 1);
    setAxisLabel("time [ns]", "a.u");

    ui->customPlot->replot();

}

KnockoutDialog::~KnockoutDialog()
{
    delete ui;
    delete customPlot;
}

void KnockoutDialog::setPlotRange(double xmin, double xmax, double ymin, double ymax)
{
    customPlot->xAxis->setRange(xmin, xmax);
    customPlot->yAxis->setRange(ymin, ymax);
}

void KnockoutDialog::setAxisLabel(QString x, QString y)
{
    // give the axes some labels:
    customPlot->xAxis->setLabel(x);
    customPlot->yAxis->setLabel(y);
}

void KnockoutDialog::setScatter(int id, bool visibleline)
{
    customPlot->graph(id)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    if (visibleline) customPlot->graph(id)->setLineStyle(QCPGraph::lsNone);

}

void KnockoutDialog::plot(int id, QString name, QVector<double> x, QVector<double> y, QPen pen)
{
    customPlot->graph(id)->setData(x, y);
    customPlot->graph(id)->setName(name);
    customPlot->graph(id)->setPen(pen); // line color blue for first graph

}

