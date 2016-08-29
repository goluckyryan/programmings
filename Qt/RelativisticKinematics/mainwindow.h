#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nucleus.h"
#include "dialog.h"
#include <QFile>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionNew_Windows_triggered();

    void displayKinematics();
    void SetMass();

    void on_pushButton_FL_clicked();
    void on_pushButton_TOF_clicked();

    void on_doubleSpinBox_KEA_valueChanged(double arg1);
    void on_doubleSpinBox_momt_valueChanged(double arg1);
    void on_doubleSpinBox_Gamma_valueChanged(double arg1);
    void on_doubleSpinBox_Beta_valueChanged(double arg1);
    void on_doubleSpinBox_Brho_valueChanged(double arg1);

    void log(QString str, bool end);

    void on_lineEdit_Z_textChanged(const QString &arg1);
    void on_lineEdit_A_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Nucleus *nu;
    Dialog *di;
    char str[200];
    bool massFlag; // calculated mass or not.

};

#endif // MAINWINDOW_H
