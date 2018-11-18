#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow{ parent },
ui{new Ui::MainWindow},
mNetwork{ new sta::NetworkManager{} },
mChart{ new sta::Chart{} } {
	//Window properties
	this->setWindowTitle("NetworkMonitor");
	this->setWindowIcon(QIcon(":/Icons/ethernet.png"));
	//ui functions
	ui->setupUi(this);
	connect(mNetwork, &sta::NetworkManager::toolbarMessage, this, &MainWindow::displayToolbarMessage);
	connect(ui->actionAutoScroll, &QAction::toggled, [this](bool a) {this->autoScrollEnabled = a; 
																	 if (autoScrollEnabled)ui->statsTableView->scrollToBottom(); });

	//on button press update deviceList and open a dialog to select desired device
	connect(ui->actionSelectAdapter, &QAction::triggered, mNetwork, &sta::NetworkManager::updateDeviceList);
	connect(ui->actionSelectAdapter, &QAction::triggered, this, &MainWindow::selectAdapterDialog);
	
	//async connection between data being read from adapter and data display
	connect(mNetwork, &sta::NetworkManager::dataRead, this, &MainWindow::packageArrived, Qt::QueuedConnection);
	//create  a table that is displayed on statsTableView
	mTable = new sta::Table{ ui->statsTableView };
	ui->statsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	//clear current data when changing adapter
	connect(mNetwork, &sta::NetworkManager::newAddapterClearData, mTable, &sta::Table::clearData);
	connect(mNetwork, &sta::NetworkManager::newAddapterClearData, mChart, &sta::Chart::clearData);

	//replace placeholder widget with proper chartview
	delete (ui->centralWidget->layout()->replaceWidget(ui->statsGraphWidget, &(mChart->chartView())));

	displayToolbarMessage("Ready", 0);
}
MainWindow::~MainWindow(){
	delete mNetwork;
	delete mChart;
	delete mTable;
    delete ui;
}
void MainWindow::selectAdapterDialog() {
	//pops out a dialog that contains a list of all available devices using their description
	QDialog selectAdapter;
	Ui_AdapterDialog dialogUi;
	dialogUi.setupUi(&selectAdapter);	

	std::vector<pcap_if_t*> devices = mNetwork->getDevices();
	for (auto device : devices)
		dialogUi.listWidget->addItem(device->description);
	auto adaptorSelected = [&selectAdapter, &dialogUi](QListWidgetItem* item)
							{selectAdapter.done(dialogUi.listWidget->row(item)); };

	connect(dialogUi.listWidget, &QListWidget::itemClicked, adaptorSelected);
	connect(dialogUi.listWidget, &QListWidget::itemEntered, adaptorSelected);

	//callbacks to connect pressing the item with calling the function on mNetwork that selects the device at that index
	connect(&selectAdapter, &QDialog::finished, mNetwork, &sta::NetworkManager::selectDevice);
	selectAdapter.exec();
}
void MainWindow::packageArrived(const std::vector<QList<QString>>& aVec, int totalSize, 
						 		QTime time){
	//send packets to tableview
	mTable->addRow(aVec); 
	if (autoScrollEnabled)
		ui->statsTableView->scrollToBottom();
	//send total bytes to graph
	mChart->addPoint(totalSize, time);
}