#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>
#include <QDebug>

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

    void on_lineEdit_yx_editingFinished();

    void on_lineEdit_x_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
