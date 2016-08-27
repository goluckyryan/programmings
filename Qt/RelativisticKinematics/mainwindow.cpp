#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::displayKinematics()
{
    ui->lineEdit_KE->setText(QString::number(nu->KEA));
    ui->lineEdit_momt->setText(QString::number(nu->Momt));
    ui->lineEdit_Gamma->setText(QString::number(nu->Gamma));
    ui->lineEdit_Beta->setText(QString::number(nu->Beta));
    ui->lineEdit_Brho->setText(QString::number(nu->Brho));
}


void MainWindow::on_pushButton_clicked()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();

    nu = new Nucleus(Z,A);

    qDebug() << nu->Z << ","<< nu->A << "," << nu->mass;
    qDebug() << "---" << nu->KEA << "," << nu->Gamma;

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
    displayKinematics();
}


void MainWindow::on_pushButton_momt_clicked()
{
    on_pushButton_clicked();
    double momt = ui->lineEdit_momt->text().toDouble();
    nu->SetMomt(momt);
    displayKinematics();

}

void MainWindow::on_pushButton_Gamma_clicked()
{
    on_pushButton_clicked();
    double g = ui->lineEdit_Gamma->text().toDouble();
    nu->SetGamma(g);
    displayKinematics();
}

void MainWindow::on_pushButton_Beta_clicked()
{
    on_pushButton_clicked();
    double b = ui->lineEdit_Beta->text().toDouble();
    nu->SetBeta(b);
    displayKinematics();
}

void MainWindow::on_pushButton_Brho_clicked()
{
    on_pushButton_clicked();
    double brho = ui->lineEdit_Brho->text().toDouble();
    nu->SetBrho(brho);
    displayKinematics();
}

void MainWindow::on_pushButton_FL_clicked()
{
    on_pushButton_clicked();
    on_pushButton_KE_clicked();
    double tof = ui->lineEdit_TOF->text().toDouble();
    nu->CalFlightLength(tof);
    ui->lineEdit_FL->setText(QString::number(nu->FLightLength));
}

void MainWindow::on_pushButton_TOF_clicked()
{
    on_pushButton_clicked();
    on_pushButton_KE_clicked();
    double fl = ui->lineEdit_FL->text().toDouble();
    nu->CalTOF(fl);
    ui->lineEdit_TOF->setText(QString::number(nu->TOF));
}
