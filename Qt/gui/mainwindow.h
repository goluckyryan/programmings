//Classes definitor


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_windows.h"
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //define a class name "MainWindow" from library "QMainWindows"
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionNew_Windows_triggered();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    New_Windows *nWindow; //a pointer name nWindow under class New_windows from "new_windows.h"

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
