#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    nu(NULL),
    knockoutDialog(NULL)
{
    ui->setupUi(this);
    knockoutDialog = new KnockoutDialog(this);

    ui->lineEdit_Z->setText("1");
    ui->lineEdit_A->setText("1");
    SetMass(1,1);
    ui->lineEdit_Z->setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete nu;
    delete knockoutDialog;
}

void MainWindow::on_actionNew_Windows_triggered()
{
    //exclusive
    //Dialog di;
    //di.setModal(false);
    //di.exec();

    //multiple instances
    //Dialog* di = new Dialog(this);
    //di->show();

    //once instance
    if( knockoutDialog->isHidden()){
        //di->setGeometry(this->geometry().width(), 50, di->geometry().width(), di->geometry().height() );
        knockoutDialog->show();
    }

    if( knockoutDialog->exec() == QDialog::Accepted){
        qDebug() << knockoutDialog->test;
    }

}

void MainWindow::displayKinematics()
{
    ui->doubleSpinBox_KEA->setValue(nu->KEA);
    ui->doubleSpinBox_momt->setValue(nu->Momt);
    ui->doubleSpinBox_Gamma->setValue(nu->Gamma);
    ui->doubleSpinBox_Beta->setValue(nu->Beta);
    ui->doubleSpinBox_Brho->setValue(nu->Brho);

}


void MainWindow::SetMass(int Z, int A)
{
    nu = new Nucleus(Z,A);

    //qDebug() << nu->Z << ","<< nu->A << "," << nu->mass;

    ui->lineEdit_Mass->setText(QString::number(nu->mass));
    ui->lineEdit_Name->setText(nu->name);
    ui->lineEdit_Sp->setText(QString::number(nu->Sp));
    ui->lineEdit_Sn->setText(QString::number(nu->Sn));
    ui->lineEdit_BEA->setText(QString::number(nu->BEA));

    sprintf(str,"Z=%2d, %3d%2s, Mass: %10.4f ",Z,A, nu->name.toStdString().c_str(), nu->mass);
    log(str, 1);

    massFlag = 1;
}

void MainWindow::SetMassbyName(QString sym)
{
    nu = new Nucleus(sym);

    ui->lineEdit_Mass->setText(QString::number(nu->mass));
    ui->lineEdit_A->setText(QString::number(nu->A));
    ui->lineEdit_Z->setText(QString::number(nu->Z));
    ui->lineEdit_Sp->setText(QString::number(nu->Sp));
    ui->lineEdit_Sn->setText(QString::number(nu->Sn));
    ui->lineEdit_BEA->setText(QString::number(nu->BEA));

    sprintf(str,"Z=%2d, %3d%2s, Mass: %10.4f ",nu->Z, nu->A, nu->name.toStdString().c_str(), nu->mass);
    log(str, 1);

    massFlag = 1;
}

void MainWindow::on_pushButton_FL_clicked()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    double tof = ui->lineEdit_TOF->text().toDouble();
    nu->CalFlightLength(tof);
    ui->lineEdit_FL->setText(QString::number(nu->FLightLength));
}

void MainWindow::on_pushButton_TOF_clicked()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    double fl = ui->lineEdit_FL->text().toDouble();
    nu->CalTOF(fl);
    ui->lineEdit_TOF->setText(QString::number(nu->TOF));
}

void MainWindow::on_doubleSpinBox_KEA_valueChanged(double arg1)
{
    arg1 = ui->doubleSpinBox_KEA->value();
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    nu->SetKEA(arg1);
    displayKinematics();
}

void MainWindow::on_doubleSpinBox_momt_valueChanged(double arg1)
{
    arg1 = ui->doubleSpinBox_momt->value();
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    nu->SetMomt(arg1);
    displayKinematics();
}

void MainWindow::on_doubleSpinBox_Gamma_valueChanged(double arg1)
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    arg1 = ui->doubleSpinBox_Gamma->value();
    nu->SetGamma(arg1);
    displayKinematics();
}

void MainWindow::on_doubleSpinBox_Beta_valueChanged(double arg1)
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    arg1 = ui->doubleSpinBox_Beta->value();
    nu->SetBeta(arg1);
    displayKinematics();
}

void MainWindow::on_doubleSpinBox_Brho_valueChanged(double arg1)
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    if( massFlag == 0 ) SetMass(Z, A);
    arg1 = ui->doubleSpinBox_Brho->value();
    nu->SetBrho(arg1);
    displayKinematics();
}

void MainWindow::log(QString str, bool end)
{
    ui->plainTextEdit->appendPlainText(str);

    QString path = QCoreApplication::applicationDirPath();
    //qDebug() << path ;
    path.append("/../../../out_Log.txt");
    QFile myfile(path);
    myfile.open(QIODevice::Append | QIODevice::Text);
    //qDebug() << myfile.fileName();

    QDateTime date = QDateTime::currentDateTime();
    myfile.write(date.toString().toStdString().c_str());
    myfile.write("\t");
    myfile.write(str.toStdString().c_str());

    if( end ) myfile.write("\n");
    myfile.close();

}

void MainWindow::on_lineEdit_Name_editingFinished()
{
    QString sym = ui->lineEdit_Name->text();
    SetMassbyName(sym);
}

void MainWindow::on_lineEdit_Z_editingFinished()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    SetMass(Z, A);
}

void MainWindow::on_lineEdit_A_editingFinished()
{
    int Z = (ui->lineEdit_Z->text()).toInt();
    int A = (ui->lineEdit_A->text()).toInt();
    SetMass(Z, A);
}
