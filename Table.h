#pragma once
#pragma region INCLUDES
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#pragma endregion
namespace sta {
	class Table : public QWidget {
		Q_OBJECT
	public:
		
		Table(QTableView*);
		~Table();
		QStandardItemModel* createTableView();
	public slots:
		//resets the graph to default view  when adapter is changed
		inline void clearData() { this->mTableModel->clear(); }
		void addRow(const std::vector<QList<QString>>&);//adds vec.size() rows to the table(each string in stringlist
														// is one field in the row)
	private:
		QStandardItemModel* mTableModel;
	};
}