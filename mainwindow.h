#pragma once
#pragma region INCLUDES
#include <QMainWindow>
#include <QDialog>
#include <QListWidget>
#include "chart.h"
#include "Table.h"
#include "ui_mainwindow.h"
#include "ui_chooseadapter.h"
#include "networkmanager.h"
#include <QtCharts/QChartView>

#pragma endregion
namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
	void packageArrived(const std::vector<QList<QString>>&, int, QTime);//package read arrived from network
	void displayToolbarMessage(QString msg, int timeout) { ui->statusBar->showMessage(msg, timeout); }
private slots:
	void selectAdapterDialog();//dialog that forces to select device to listen
private:
    Ui::MainWindow* ui;//window design
	sta::NetworkManager*  mNetwork;//network class doing data read work
	sta::Table* mTable;//displaying data in a table
	sta::Chart* mChart;//displaying data as a chart
	bool autoScrollEnabled = false;//autoscroll funcionality enabled/disabled
};