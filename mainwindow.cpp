#include "mainwindow.h"
#include "AliasDialog.h"
#include "DrawerWidget.h"
#include "ui_mainwindow.h"
#include "ui_chooseadapter.h"
#include "JsonParser.h"
#include "chart.h"
#include "Table.h"
#include "networkmanager.h"
MainWindow::MainWindow(QWidget *parent) :
							QMainWindow{ parent },
							mUi{new Ui::MainWindow},
							mNetwork{ new sta::NetworkManager{} },
							mChart{ new sta::Chart{} }{
	//setup this window
	this->setupWindow();
	
	//update aliases file
	mJsonFile.setFileName("persistent.json");

	mNetwork->setAliases(sta::JsonParser::readAliasesFromFile(mJsonFile));
	connect(mNetwork, &sta::NetworkManager::aliasesChanged, this, &MainWindow::updateAliasesFile);
	//update settings
	this->loadSettingsFromFile();
	mDrawerWidget->loadInitialSettings();//new values set
	//update dnsCache
	this->loadIpDnsCacheFromFile();

	//on button press update deviceList and open a dialog to select desired device
	connect(mUi->actionSelectAdapter, &QAction::triggered, mNetwork, &sta::NetworkManager::updateDeviceList);
	connect(mUi->actionSelectAdapter, &QAction::triggered, this, &MainWindow::selectAdapterDialog);
	
	//open up dialog with aliases
	connect(mUi->actionMapAddress, &QAction::triggered, this, &MainWindow::selectAliasesDialog);

	//async connection between data being read from adapter and data display
	connect(mNetwork, &sta::NetworkManager::dataRead, this, &MainWindow::packageArrived, Qt::QueuedConnection);

	//clear current data when changing adapter
	connect(mNetwork, &sta::NetworkManager::newAdapterClearData, mTable, &sta::Table::clearData);
	connect(mNetwork, &sta::NetworkManager::newAdapterClearData, mChart, &sta::Chart::clearData);
	connect(mNetwork, &sta::NetworkManager::newAdapterClearData, mDrawerWidget, &sta::DrawerWidget::clearFilter);

	displayToolbarMessage("Ready", 0);
}
MainWindow::~MainWindow() {
	//write settings
	std::map<QString, QString> settingsMap;
	for (auto& button : mUi->mainToolBar->allButtons())
		if (button->isCheckable())
			settingsMap[button->objectName()] = QString::number(button->isChecked());
	for (const auto& lineEdit : mDrawerWidget->persistentLineEdits())
		settingsMap[lineEdit->objectName()] = lineEdit->text();

	sta::JsonParser::writeSettingsToFile(settingsMap, mJsonFile);

	//write ip
	if (mUi->actionSaveIpToDns->isChecked()) 
		sta::JsonParser::writeIpCacheToFile(mNetwork->getIpDnsCache(), mJsonFile);
	
	delete mNetwork;
	delete mChart;
	delete mTable;
    delete mUi;
}
void MainWindow::packageArrived(const std::vector<QList<QString>>& aVec, int totalSize, 
						 		QTime time){
	//send packets to tableview
	mTable->addRows(aVec);
	if (mUi->actionAutoScroll->isEnabled())
		mUi->statsTableView->scrollToBottom();
	//send total bytes to graph
	mChart->addPoint(totalSize, time);
}
void MainWindow::displayToolbarMessage(QString msg, int timeout){
	mUi->statusBar->showMessage(msg, timeout);
}
void MainWindow::setAliases(const std::map<QString, QString>& map) {
	mNetwork->setAliases(map);
}
std::map<QString, QString> MainWindow::getAliases() const {
	return mNetwork->getAliases();
}
void MainWindow::updateAliasesFile() { 
	sta::JsonParser::writeAliasesToFile(mNetwork->getAliases(), mJsonFile); 
}
void MainWindow::selectAdapterDialog() {
	//pops out a dialog that contains a list of all available devices using their description
	QDialog selectAdapter{this};
	Ui_AdapterDialog dialogUi;
	dialogUi.setupUi(&selectAdapter);	

	selectAdapter.setWindowIcon(QIcon(":/Icons/adapter.png"));
	std::vector<pcap_if_t*> devices = mNetwork->getDevices();
	for (const auto& device : devices)
		dialogUi.listWidget->addItem(device->description);
		
	auto adaptorSelected = [&selectAdapter, &dialogUi](QListWidgetItem* item)
							{selectAdapter.done(dialogUi.listWidget->row(item) + 2); };
	//the dialog will return a value of: 0->rejected
	//								     1->accepted
	//									 x->the value we put in .done(int)
	//so to know if it was our value or reject/accept, we make x>=2 by doing x+=2,
	//test the result and if its our value we map back x-=2

	connect(dialogUi.listWidget, &QListWidget::itemClicked, adaptorSelected);
	connect(dialogUi.listWidget, &QListWidget::itemEntered, adaptorSelected);

	//callbacks to connect pressing the item with calling the function on mNetwork that selects the device at that index
	connect(&selectAdapter, &QDialog::finished, [this](int i) 
	{if(i >= 2) mNetwork->selectDevice(i - 2); });
	selectAdapter.exec();
}
void MainWindow::selectAliasesDialog(){  
	auto mAliasDialog = new sta::AliasDialog{ this }; //device aliases
}
void MainWindow::drawerDialog() {
	mUi->actionOpenMenu->isChecked() ? mDrawerWidget->openDrawer() : mDrawerWidget->closeDrawer();	
}
void MainWindow::loadSettingsFromFile() {
	auto settingsMap = sta::JsonParser::readSettingsFromFile(mJsonFile);

	for (auto& button : mUi->mainToolBar->allButtons())
		if (button->isCheckable()) {
			if (auto it = settingsMap.find(button->objectName()); it != settingsMap.end())
				button->setChecked(stringToBool(it->second));
			else
				button->setChecked(false);
		}
	for (const auto& lineEdit : mDrawerWidget->persistentLineEdits())
		if (auto it = settingsMap.find(lineEdit->objectName()); it != settingsMap.end())
			lineEdit->insert(it->second);		
		
}
void MainWindow::loadIpDnsCacheFromFile() {
	mNetwork->setIpDnsCache(sta::JsonParser::readIpCacheFromFile(mJsonFile));
}
bool MainWindow::stringToBool(const QString& string) {
	return(string == "1" || string.toLower() == "true");
}
void MainWindow::setupWindow() {
	//Window properties
	this->setWindowTitle("NetworkMonitor");
	this->setWindowIcon(QIcon(":/Icons/ethernet.png"));
	//mUi functions
	mUi->setupUi(this);

	QWidget* spacerWidget = new QWidget(this);
	spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	spacerWidget->setVisible(true);

	mUi->mainToolBar->addWidget(spacerWidget);
	mUi->mainToolBar->addAction(mUi->actionOpenMenu);

	//create  a table that is displayed on statsTableView
	mTable = new sta::Table{ mUi->statsTableView };
	mUi->statsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//replace placeholder widget with proper chartview
	delete (mUi->centralWidget->layout()->replaceWidget(mUi->statsGraphWidget, &(mChart->chartView())));
	mDrawerWidget = new sta::DrawerWidget {mUi->menuWidget, this};


	connect(mDrawerWidget, &sta::DrawerWidget::maxRowsNumberChanged, mTable, &sta::Table::setNumberOfRows);
	connect(mDrawerWidget, &sta::DrawerWidget::installFilter, mNetwork, &sta::NetworkManager::installFilter);
	connect(mNetwork, &sta::NetworkManager::filterInstalled, mDrawerWidget, &sta::DrawerWidget::filterInstalled);
	connect(mNetwork, &sta::NetworkManager::toolbarMessage, this, &MainWindow::displayToolbarMessage);
	connect(mUi->actionAutoScroll, &QAction::toggled, [this]() { if (mUi->actionAutoScroll->isChecked())mUi->statsTableView->scrollToBottom(); });
	connect(mUi->actionOpenMenu, &QAction::toggled, this, &MainWindow::drawerDialog);
}

//IterableToolbar CLASS
IterableToolbar::IterableToolbar(const QString& title, QWidget* parent) :QToolBar{ title, parent } {}
IterableToolbar::IterableToolbar(QWidget* parent) : QToolBar{ parent } {}
void IterableToolbar::addAction(QAction* action){
	QToolBar::addAction(action);
	mButtons.push_back(action);
}
std::vector<QAction*> IterableToolbar::allButtons() {
	return mButtons;
}