#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "nucleus.h"
#include "dialog.h"

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

    void on_pushButton_clicked();

    void on_pushButton_KE_clicked();

private:
    Ui::MainWindow *ui;
    //Nucleus *nu;

};

#endif // MAINWINDOW_H
