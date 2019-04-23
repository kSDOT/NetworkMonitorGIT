#pragma once
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
namespace sta {
	class Table : public QWidget {
		Q_OBJECT
	public:
		Q_PROPERTY(int maxNumberOfRows READ getNumberOfRows WRITE setNumberOfRows  NOTIFY numberOfRowsChanged)
	
		Table(QTableView*);
		~Table();
		QStandardItemModel* createTableView();
	signals:
		void numberOfRowsChanged(int);
	public slots:
		//resets the graph to default view  when adapter is changed
		 void clearData();
		void addRows(const std::vector<QList<QString>>&);//adds vec.size() rows to the table(each string in stringlist
																									// is one field in the row)	
		void setNumberOfRows(int);
		int getNumberOfRows() const;
	private:
		QStandardItemModel* mTableModel;
		int mMaxNumberOfRows;
	};
}