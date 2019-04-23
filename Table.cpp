#include "table.h"
namespace sta {
	Table::Table(QTableView* table) :mTableModel{ new QStandardItemModel{} } {
		table->setModel(createTableView());
	}
	Table::~Table() {
		delete mTableModel;
	}
	QStandardItemModel* Table::createTableView(){
		mTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Time")));
		mTableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Source")));
		mTableModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Destination")));
		mTableModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Protocol")));
		return mTableModel;
	}
	void Table::clearData() { 
		mTableModel->setRowCount(0); 
	}
	void Table::addRows(const std::vector<QList<QString>>& aVec) {
		QList<QStandardItem*> rowData;//transform stringlist to standarditemlist
		for (auto& list : aVec) {
			for (auto& string : list)
				rowData << new QStandardItem{ string };
			mTableModel->appendRow(rowData);//append each row and reset the list
			rowData.clear();
		}
		if (int rowCount = mTableModel->rowCount(); 
			rowCount > mMaxNumberOfRows)
			mTableModel->removeRows(0,  rowCount - mMaxNumberOfRows );
		
	}
	void Table::setNumberOfRows(int newNumber) {
		if (mMaxNumberOfRows != newNumber) {
			mMaxNumberOfRows = newNumber;
			emit numberOfRowsChanged(mMaxNumberOfRows);
		}
	}
	int Table::getNumberOfRows() const { 
		return mMaxNumberOfRows; 
	}
}