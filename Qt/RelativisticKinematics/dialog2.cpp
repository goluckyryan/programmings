#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_radioButton_clicked()
{
    ui->lineEdit->setText("1");
}

void Dialog2::on_radioButton_2_clicked()
{
    ui->lineEdit->setText("2");
}
