#ifndef NEW_WINDOWS_H
#define NEW_WINDOWS_H

#include <QDialog>

namespace Ui {
class New_Windows;
}

class New_Windows : public QDialog
{
    Q_OBJECT
    
public:
    explicit New_Windows(QWidget *parent = 0);
    ~New_Windows();
    
private:
    Ui::New_Windows *ui;
};

#endif // NEW_WINDOWS_H
