/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainwindow.h>
#include "Chart.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSelectAdapter;
    QAction *actionAutoScroll;
    QAction *actionMapAddress;
    QAction *actionSaveIpToDns;
    QAction *actionOpenMenu;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *statsTableView;
    QSpacerItem *verticalSpacer;
    sta::Chart *statsGraphWidget;
    QWidget *menuWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *maxRowsLineEdit;
    QLineEdit *filterLineEdit;
    QLabel *installedFiltersLineEdit;
    QLabel *maxRowsLabel;
    QLabel *filter;
    QTextBrowser *installedFiltersTextBrowser;
    QMenuBar *menuBar;
    IterableToolbar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1153, 585);
        actionSelectAdapter = new QAction(MainWindow);
        actionSelectAdapter->setObjectName(QString::fromUtf8("actionSelectAdapter"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/adapter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectAdapter->setIcon(icon);
        actionAutoScroll = new QAction(MainWindow);
        actionAutoScroll->setObjectName(QString::fromUtf8("actionAutoScroll"));
        actionAutoScroll->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/autoScroll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAutoScroll->setIcon(icon1);
        actionMapAddress = new QAction(MainWindow);
        actionMapAddress->setObjectName(QString::fromUtf8("actionMapAddress"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/translate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMapAddress->setIcon(icon2);
        actionSaveIpToDns = new QAction(MainWindow);
        actionSaveIpToDns->setObjectName(QString::fromUtf8("actionSaveIpToDns"));
        actionSaveIpToDns->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveIpToDns->setIcon(icon3);
        actionOpenMenu = new QAction(MainWindow);
        actionOpenMenu->setObjectName(QString::fromUtf8("actionOpenMenu"));
        actionOpenMenu->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenMenu->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        statsTableView = new QTableView(centralWidget);
        statsTableView->setObjectName(QString::fromUtf8("statsTableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statsTableView->sizePolicy().hasHeightForWidth());
        statsTableView->setSizePolicy(sizePolicy);
        statsTableView->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(statsTableView);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        statsGraphWidget = new sta::Chart(centralWidget);
        statsGraphWidget->setObjectName(QString::fromUtf8("statsGraphWidget"));
        sizePolicy.setHeightForWidth(statsGraphWidget->sizePolicy().hasHeightForWidth());
        statsGraphWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(statsGraphWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        menuWidget = new QWidget(centralWidget);
        menuWidget->setObjectName(QString::fromUtf8("menuWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(menuWidget->sizePolicy().hasHeightForWidth());
        menuWidget->setSizePolicy(sizePolicy1);
        menuWidget->setMinimumSize(QSize(0, 0));
        menuWidget->setMaximumSize(QSize(300, 16777215));
        gridLayoutWidget = new QWidget(menuWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 301, 144));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        maxRowsLineEdit = new QLineEdit(gridLayoutWidget);
        maxRowsLineEdit->setObjectName(QString::fromUtf8("maxRowsLineEdit"));

        gridLayout->addWidget(maxRowsLineEdit, 0, 1, 1, 1);

        filterLineEdit = new QLineEdit(gridLayoutWidget);
        filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));

        gridLayout->addWidget(filterLineEdit, 1, 1, 1, 1);

        installedFiltersLineEdit = new QLabel(gridLayoutWidget);
        installedFiltersLineEdit->setObjectName(QString::fromUtf8("installedFiltersLineEdit"));

        gridLayout->addWidget(installedFiltersLineEdit, 2, 0, 1, 1);

        maxRowsLabel = new QLabel(gridLayoutWidget);
        maxRowsLabel->setObjectName(QString::fromUtf8("maxRowsLabel"));

        gridLayout->addWidget(maxRowsLabel, 0, 0, 1, 1);

        filter = new QLabel(gridLayoutWidget);
        filter->setObjectName(QString::fromUtf8("filter"));

        gridLayout->addWidget(filter, 1, 0, 1, 1);

        installedFiltersTextBrowser = new QTextBrowser(gridLayoutWidget);
        installedFiltersTextBrowser->setObjectName(QString::fromUtf8("installedFiltersTextBrowser"));

        gridLayout->addWidget(installedFiltersTextBrowser, 2, 1, 1, 1);


        horizontalLayout_2->addWidget(menuWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1153, 21));
        menuBar->setMinimumSize(QSize(0, 0));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new IterableToolbar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 30));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionSelectAdapter);
        mainToolBar->addAction(actionMapAddress);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAutoScroll);
        mainToolBar->addAction(actionSaveIpToDns);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSelectAdapter->setText(QApplication::translate("MainWindow", "SelectAdapter", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSelectAdapter->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Select the adapter to analyze data from.</p><p><span style=\" font-style:italic;\">(Ctrl+ A)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSelectAdapter->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionAutoScroll->setText(QApplication::translate("MainWindow", "AutoScroll", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAutoScroll->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Autoscroll the table</p><p><span style=\" font-style:italic;\">(Ctrl+ Q)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionAutoScroll->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionMapAddress->setText(QApplication::translate("MainWindow", "MapAddress", nullptr));
#ifndef QT_NO_TOOLTIP
        actionMapAddress->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Maps specific IP addresses to aliases.</p><p><span style=\" font-style:italic;\">(Ctrl+ T)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMapAddress->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_NO_SHORTCUT
        actionSaveIpToDns->setText(QApplication::translate("MainWindow", "SaveIpToDns", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveIpToDns->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Enable to save the translated ip addresses before exit.<br/><span style=\" font-style:italic;\">(Ctrl + I)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSaveIpToDns->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpenMenu->setText(QApplication::translate("MainWindow", "OpenMenu", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenMenu->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Open settings and data usage per device drawer.</p><p><span style=\" font-style:italic;\">(Ctrl + M)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpenMenu->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        installedFiltersLineEdit->setText(QApplication::translate("MainWindow", "Installed Filters", nullptr));
        maxRowsLabel->setText(QApplication::translate("MainWindow", "Max number of rows in table", nullptr));
        filter->setText(QApplication::translate("MainWindow", "Install Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
