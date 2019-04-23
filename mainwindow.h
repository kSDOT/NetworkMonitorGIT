#pragma once
#pragma region INCLUDES
#include <QMainWindow>
#include <QListWidget>
#include <QDialog>
#include <QToolBar>
#include <QtCharts/QChartView>
#include <QTime>
#pragma endregion

namespace Ui {
    class MainWindow;
    }
namespace sta{
	class AliasDialog;
	class DrawerWidget;
	class NetworkManager;
	class Chart;
	class Table;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
	Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();	
public slots:
	void packageArrived(const std::vector<QList<QString>>&, int, QTime);//package read arrived from network
	void displayToolbarMessage(QString, int );

	void setAliases(const std::map<QString, QString>&);
	std::map<QString, QString> getAliases() const;
private slots:
	void updateAliasesFile();
	void selectAdapterDialog();//dialog that forces to select device to listen
	void selectAliasesDialog();//dialog to view/edit aliases
	void drawerDialog();//testing drawer funcionality
private://FUNCTIONS
	void loadSettingsFromFile();
	void loadIpDnsCacheFromFile();
	bool stringToBool(const QString&);
	void setupWindow();
private: //MEMBER DATA
    Ui::MainWindow* mUi;//window design
	sta::NetworkManager*  mNetwork;//network class doing data read work
	sta::Table* mTable;//displaying data in a table
	sta::Chart* mChart;//displaying data as a chart
	sta::AliasDialog* mAliasDialog;//dialog to display/modify aliases
	sta::DrawerWidget* mDrawerWidget;//make sliding animation for widget
	QFile mJsonFile;

};

class IterableToolbar : public QToolBar {
public:
	IterableToolbar(const QString& title, QWidget* parent = 0);
	IterableToolbar(QWidget* parent = 0);
	void addAction(QAction* action);//not overridable :(
	std::vector<QAction*> allButtons();
private:
	std::vector<QAction*> mButtons;
};
