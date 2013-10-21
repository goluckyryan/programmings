#include "mainwindow.h"
#include "ui_mainwindow.h"

const double pi = 3.141592458;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush blackbrush(Qt::black);
    QPen redpen(Qt::red);
    QPen bluepen(Qt::blue);
    redpen.setWidth(2);
    bluepen.setWidth(2);

    ellipse = scene->addEllipse(0,0,10,10,redpen, blackbrush);
    ellipse2 = scene->addEllipse(40,0,10,10,bluepen, blackbrush);
    //ellipse->setFlag(QGraphicsItem::ItemIsMovable);
    QFont f;
    f.setStyleHint(QFont::OldEnglish);
    f.setPixelSize(10);
    coordx=scene->addText("(0,0)", f);
    coordx->setPos(ellipse->x()+10,ellipse->y());
    coord1=scene->addText("(40,0)",f);
    coord1->setPos(ellipse2->x()+50,ellipse2->y());
    coordang=scene->addText("0 deg",f);
    coordang->setPos(ellipse2->x()+50,ellipse2->y()+15);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawEllipse(100,100,70,50);

    QTextDocument doc;
    QRect rec(50, 50, 250,250);
    QRect rec2(0,0,100,100);
    painter.drawRect(rec);
    painter.translate(50,50);
    painter.drawText(rec, Qt::AlignLeft | Qt::AlignVCenter, "Left");
    doc.setTextWidth(100);
    doc.setHtml("<b> Hello </b>");
    doc.drawContents(&painter, rec2);

    QPen pen1(Qt::red);
    pen1.setWidth(4);

    QPen pen2(Qt::blue);
    pen2.setWidth(4);

    QPen pen3(Qt::green);
    pen3.setWidth(4);

    QRect rec3(100,100,100,50);

    painter.setPen(pen1);
    painter.drawRect(rec3);
    painter.drawRect(rec2);

    painter.translate(100,0);
    painter.rotate(45);
    painter.setPen(pen2);
    painter.drawRect(rec3);
    painter.drawRect(rec2);

}*/


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ellipse->setPos(value,ellipse->y());
    coordx->setHtml(QString("(%1,%2)").arg(ellipse->x()).arg(ellipse->y()));
    coordx->setX(ellipse->x()+10);
}


void MainWindow::on_verticalScrollBar_valueChanged(int value)
{
    ellipse->setPos(ellipse->x(),value);
    coordx->setHtml(QString("(%1,%2)").arg(ellipse->x()).arg(ellipse->y()));
    coordx->setY(ellipse->y());
}

void MainWindow::on_dial_valueChanged(int value)
{
    ellipse2->setPos(-40+40*cos((value-90)*pi/180),-40*sin((value-90)*pi/180));
    coord1->setHtml(QString("(%1,%2)").arg(ellipse2->x()+40).arg(ellipse2->y()));
    coord1->setPos(ellipse2->x()+50,ellipse2->y());
    coordang->setHtml(QString("%1 deg").arg(value-90));
    coordang->setPos(ellipse2->x()+50,ellipse2->y()+15);
}
