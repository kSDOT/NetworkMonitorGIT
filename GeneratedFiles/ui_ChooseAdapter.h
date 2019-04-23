/********************************************************************************
** Form generated from reading UI file 'ChooseAdapter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEADAPTER_H
#define UI_CHOOSEADAPTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdapterDialog
{
public:
    QGroupBox *groupBox;
    QListWidget *listWidget;

    void setupUi(QWidget *AdapterDialog)
    {
        if (AdapterDialog->objectName().isEmpty())
            AdapterDialog->setObjectName(QString::fromUtf8("AdapterDialog"));
        AdapterDialog->resize(605, 211);
        groupBox = new QGroupBox(AdapterDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 591, 196));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(7, 20, 579, 166));

        retranslateUi(AdapterDialog);

        QMetaObject::connectSlotsByName(AdapterDialog);
    } // setupUi

    void retranslateUi(QWidget *AdapterDialog)
    {
        AdapterDialog->setWindowTitle(QApplication::translate("AdapterDialog", "Choose Adapter", nullptr));
        groupBox->setTitle(QApplication::translate("AdapterDialog", "Select Adapter to open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdapterDialog: public Ui_AdapterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEADAPTER_H
