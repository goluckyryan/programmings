#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nuclei_mass.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    nu(NULL)
{
    ui->setupUi(this);
    //ui->lineEdit_Z->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Windows_triggered()
{
    //exclusive
    Dialog di;
    di.setModal(true);
    di.exec();
    //multiple instances
    //Dialog* di = new Dialog(this);
    //di->show();
}


void MainWindow::on_pushButton_clicked()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();

    nu = new Nucleus(Z,A);

    qDebug() << nu->Z << ","<< nu->A << "," << nu->mass;

    ui->lineEdit_Mass->setText(QString::number(nu->mass));
    ui->lineEdit_Name->setText(nu->name);
    ui->lineEdit_Sp->setText(QString::number(nu->Sp));
    ui->lineEdit_Sn->setText(QString::number(nu->Sn));
    ui->lineEdit_BEA->setText(QString::number(nu->BEA));

}

void MainWindow::on_pushButton_KE_clicked()
{
    on_pushButton_clicked();

    double KEA = ui->lineEdit_KE->text().toDouble();

    nu->SetKEA(KEA);

    ui->lineEdit_KE->setText(QString::number(KEA));
    ui->lineEdit_momt->setText(QString::number(nu->Momt));

}

