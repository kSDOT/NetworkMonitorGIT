/********************************************************************************
** Form generated from reading UI file 'Aliases.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIASES_H
#define UI_ALIASES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_aliasesDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *aliasesTable;

    void setupUi(QDialog *aliasesDialog)
    {
        if (aliasesDialog->objectName().isEmpty())
            aliasesDialog->setObjectName(QString::fromUtf8("aliasesDialog"));
        aliasesDialog->resize(605, 350);
        buttonBox = new QDialogButtonBox(aliasesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(440, 310, 156, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        aliasesTable = new QTableWidget(aliasesDialog);
        aliasesTable->setObjectName(QString::fromUtf8("aliasesTable"));
        aliasesTable->setGeometry(QRect(10, 10, 586, 291));

        retranslateUi(aliasesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), aliasesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), aliasesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(aliasesDialog);
    } // setupUi

    void retranslateUi(QDialog *aliasesDialog)
    {
        aliasesDialog->setWindowTitle(QApplication::translate("aliasesDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aliasesDialog: public Ui_aliasesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIASES_H
