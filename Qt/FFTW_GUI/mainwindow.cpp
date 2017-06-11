#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot = ui->widget;

    plot->axisRect()->setupFullAxesBox(true);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");

    colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
    colorMap->clearData();

    nx = 5000;
    ny = 2000;

    data = new QVector<double> [ny];
    fdataA = new QVector<double> [ny];

    for( int i = 0; i < ny; i++){
        for(int j = 0; j < nx; j++){
            //data[i].push_back( cos(2*M_PI*i/1000) * sin(2*M_PI*j/1000) );
            //data[i].push_back( exp(-pow(i-1000,2)/1000000)* exp(-pow(j-500,2)/100000) );
            data[i].push_back( exp(-pow(i-1000,2)/1000000)* exp(-pow(j-3000,4)/100000) );
        }
    }

    colorMap->data()->setSize(nx,ny);

    for( int i = 0; i < ny; i++){
        for(int j = 0; j < nx; j++){
            colorMap->data()->setCell(j,i,data[i][j]);
        }
    }

    colorMap->setGradient(QCPColorGradient::gpJet );
    colorMap->setDataScaleType(QCPAxis::stLinear);
    colorMap->rescaleDataRange();

    plot->rescaleAxes();
    plot->replot();

}



MainWindow::~MainWindow()
{
    delete [] data;
    delete [] fdataA;

    delete colorMap;
    delete plot;
    delete ui;
}

void MainWindow::FouierForward()
{

    qDebug() << "initial in and out";

    fftw_complex *in, *out;
    in = (fftw_complex* ) fftw_alloc_complex(ny*nx*sizeof(fftw_complex));
    out = (fftw_complex* ) fftw_alloc_complex(ny*nx*sizeof(fftw_complex));

    qDebug() << "make plan";
    fftw_plan plan;
    plan = fftw_plan_dft_2d(ny, nx, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    qDebug() << "fill data";
    for( int i = 0; i < ny ; i++){
        for( int j = 0; j < nx ; j++){
            in[i*nx + j][0] = data[i][j];
            in[i*nx + j][1] = 0;
        }
    }

    qDebug() << "FFTW";
    fftw_execute(plan);

    qDebug() << "save result";
    for( int i = 0; i < ny; i++){
            fdataA[i].clear();
        for(int j = 0; j < nx; j++){
            fdataA[i].push_back(out[i*nx + j][0] );
        }
    }
    //qDebug() << fdataA[0];

    qDebug() << "clean up";
    fftw_destroy_plan(plan);
    fftw_free(out);
    fftw_free(in);

}

void MainWindow::on_pushButton_clicked()
{
    FouierForward();

    //colorMap->data()->clear();

    for( int i = 0; i < ny; i++){
        for(int j = 0; j < nx; j++){
            colorMap->data()->setCell(j,i,fdataA[i][j]);
        }
    }

    //colorMap->setGradient(QCPColorGradient::gpJet );
    colorMap->rescaleDataRange();
    colorMap->setDataScaleType(QCPAxis::stLogarithmic);

    //plot->rescaleAxes();
    plot->replot();
}
