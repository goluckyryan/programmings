/********************************************************************************
** Form generated from reading UI file 'new_windows.ui'
**
** Created: Sun Apr 1 14:59:14 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_WINDOWS_H
#define UI_NEW_WINDOWS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_New_Windows
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *New_Windows)
    {
        if (New_Windows->objectName().isEmpty())
            New_Windows->setObjectName(QString::fromUtf8("New_Windows"));
        New_Windows->resize(400, 300);
        widget = new QWidget(New_Windows);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 361, 241));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 1, 0);
        plainTextEdit = new QPlainTextEdit(widget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(New_Windows);
        QObject::connect(buttonBox, SIGNAL(accepted()), New_Windows, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), New_Windows, SLOT(reject()));

        QMetaObject::connectSlotsByName(New_Windows);
    } // setupUi

    void retranslateUi(QDialog *New_Windows)
    {
        New_Windows->setWindowTitle(QApplication::translate("New_Windows", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class New_Windows: public Ui_New_Windows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_WINDOWS_H
