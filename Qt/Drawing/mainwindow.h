#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QString>
#include <QtGlobal>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsEllipseItem *ellipse2;
    QGraphicsTextItem *coordx;
    QGraphicsTextItem *coord1;
    QGraphicsTextItem *coordang;
protected:
    //void paintEvent(QPaintEvent *e);
private slots:
    void on_horizontalScrollBar_valueChanged(int value);
    void on_verticalScrollBar_valueChanged(int value);
    void on_dial_valueChanged(int value);
};

#endif // MAINWINDOW_H
