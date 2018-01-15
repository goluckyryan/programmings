#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_yx_editingFinished()
{

}

void MainWindow::on_lineEdit_x_editingFinished()
{
    QScriptEngine scriptEngine;
    QString expression = ui->lineEdit_yx->text();
    QString x = ui->lineEdit_x->text();

    //need to replace x in the expression;

    QScriptValue ans = scriptEngine.evaluate(expression);

    qDebug() << 2;
    qDebug() << ans.toNumber();
}
