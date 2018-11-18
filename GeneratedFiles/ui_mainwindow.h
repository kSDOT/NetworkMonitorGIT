/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSelectAdapter;
    QAction *actionAutoScroll;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableView *statsTableView;
    QSpacerItem *verticalSpacer;
    QWidget *statsGraphWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(603, 480);
        actionSelectAdapter = new QAction(MainWindow);
        actionSelectAdapter->setObjectName(QStringLiteral("actionSelectAdapter"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/adapter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectAdapter->setIcon(icon);
        actionAutoScroll = new QAction(MainWindow);
        actionAutoScroll->setObjectName(QStringLiteral("actionAutoScroll"));
        actionAutoScroll->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/autoScroll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAutoScroll->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        statsTableView = new QTableView(centralWidget);
        statsTableView->setObjectName(QStringLiteral("statsTableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statsTableView->sizePolicy().hasHeightForWidth());
        statsTableView->setSizePolicy(sizePolicy);
        statsTableView->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(statsTableView);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        statsGraphWidget = new QWidget(centralWidget);
        statsGraphWidget->setObjectName(QStringLiteral("statsGraphWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statsGraphWidget->sizePolicy().hasHeightForWidth());
        statsGraphWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(statsGraphWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 603, 21));
        menuBar->setMinimumSize(QSize(0, 0));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 30));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionSelectAdapter);
        mainToolBar->addAction(actionAutoScroll);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSelectAdapter->setText(QApplication::translate("MainWindow", "SelectAdapter", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSelectAdapter->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Select the adapter to analyze data from.</p><p><span style=\" font-style:italic;\">(Ctrl + A)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSelectAdapter->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionAutoScroll->setText(QApplication::translate("MainWindow", "AutoScroll", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAutoScroll->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Autoscroll the table</p><p><span style=\" font-style:italic;\">(Ctrl + Q)</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionAutoScroll->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
