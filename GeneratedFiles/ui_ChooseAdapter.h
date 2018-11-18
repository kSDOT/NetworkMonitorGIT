/********************************************************************************
** Form generated from reading UI file 'ChooseAdapter.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEADAPTER_H
#define UI_CHOOSEADAPTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdapterDialog
{
public:
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QWidget *AdapterDialog)
    {
        if (AdapterDialog->objectName().isEmpty())
            AdapterDialog->setObjectName(QStringLiteral("AdapterDialog"));
        AdapterDialog->resize(702, 211);
        label = new QLabel(AdapterDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 1, 691, 20));
        listWidget = new QListWidget(AdapterDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(1, 21, 701, 189));

        retranslateUi(AdapterDialog);

        QMetaObject::connectSlotsByName(AdapterDialog);
    } // setupUi

    void retranslateUi(QWidget *AdapterDialog)
    {
        AdapterDialog->setWindowTitle(QApplication::translate("AdapterDialog", "Choose Adapter", nullptr));
        label->setText(QApplication::translate("AdapterDialog", "Select adapter to open:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdapterDialog: public Ui_AdapterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEADAPTER_H
