#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_windows.h"
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            ui->progressBar,SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen paintpen(Qt::black);
    paintpen.setWidth(6);

    QPen linepen(Qt::red);
    linepen.setWidth(2);

    QPoint p1;
    p1.setX(100);
    p1.setY(100);
    QPoint p2;
    p2.setX(200);
    p2.setY(200);

    painter.setPen(linepen);
    painter.drawLine (100+ui->horizontalSlider->value(),100,300,300);
}


void MainWindow::on_actionNew_Windows_triggered()
{
    nWindow = new New_Windows(this); //the QMainwindows is the parent window
    nWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->progressBar->setValue(50);
    ui->horizontalSlider->setValue(50);
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QString msg;
    QTextStream(&msg) << position << "%";
    ui->label->setText(msg);

}

