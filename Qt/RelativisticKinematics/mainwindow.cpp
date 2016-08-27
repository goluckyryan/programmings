#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nuclei_mass.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    double mass = Nucleus_Mass(Z,A);
    QString name = Nucleus_Name(Z,A);
    double Sp = SeparationEnergy(Z, A, 0, 1);
    double Sn = SeparationEnergy(Z, A, 1, 0);
    double BEA = (Z*mp + (A-Z)*mn - mass )/A;

    qDebug() << Z << ","<< A << "," << mass;

    ui->lineEdit_Mass->setText(QString::number(mass));
    ui->lineEdit_Name->setText(name);
    ui->lineEdit_Sp->setText(QString::number(Sp));
    ui->lineEdit_Sn->setText(QString::number(Sn));
    ui->lineEdit_BEA->setText(QString::number(BEA));
}

void MainWindow::on_pushButton_KE_clicked()
{
    on_pushButton_clicked();

    double mass = ui->lineEdit_Mass->text().toDouble();
    int A = ui->lineEdit_A->text().toInt();
    double KE = ui->lineEdit_KE->text().toDouble() * A;

    double gamma = (KE + mass) / mass;
    double beta = sqrt(1- 1/gamma/gamma);
    double Momt = mass * gamma * beta;

    double KEA = ui->lineEdit_KE->text().toDouble();

    ui->lineEdit_KE->setText(QString::number(KEA));
    ui->lineEdit_momt->setText(QString::number(Momt));

}

