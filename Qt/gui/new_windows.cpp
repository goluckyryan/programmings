#include "new_windows.h"
#include "ui_new_windows.h"

New_Windows::New_Windows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Windows)
{
    ui->setupUi(this);
}

New_Windows::~New_Windows()
{
    delete ui;
}
