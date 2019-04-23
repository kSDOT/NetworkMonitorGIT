#include "AliasDialog.h"
#include "mainwindow.h"

namespace sta{
AliasDialog::AliasDialog(MainWindow* parent) : QWidget{parent}, mAliases{ new QDialog{this} }, mAliasesUi{ new Ui_aliasesDialog{} } {
	
	this->setAttribute(Qt::WA_DeleteOnClose, true);
	mAliasesUi->setupUi(mAliases);
	mAliases->setWindowIcon(QIcon(":/Icons/translate.png"));
	mAliasesUi->buttonBox->button(QDialogButtonBox::Ok)->setWhatsThis("Press OK to save changes made to the table");
	mAliasesUi->buttonBox->button(QDialogButtonBox::Cancel)->setWhatsThis("Press CANCEL to cancel changes made to the table");
	KeyPressEventFilter filter{};
	mAliases->installEventFilter(&filter);
	connect(&filter, &KeyPressEventFilter::keyDeleteRow, this, &AliasDialog::deleteRow);
	connect(&filter, &KeyPressEventFilter::enterCell, [this]() {
		mAliasesUi->aliasesTable->editItem(mAliasesUi->aliasesTable->currentItem()); });

	mTempMap = qobject_cast<MainWindow*>(this->parent())->getAliases();
	setupTable();

	setupButton();

	connect(mAliases, &QDialog::finished, [this](int result) {
		if (result == QDialog::Accepted)
			qobject_cast<MainWindow*>(this->parent())->setAliases(this->mTempMap); });
	
	connect(this, &AliasDialog::deleteAnimationFinished, [this](QTableWidgetItem* firstCell, QTableWidgetItem*) {
		mAliasesUi->aliasesTable->removeRow(firstCell->row());
		emit updateButtonGeometryRequest();
	});

	mAliases->exec();
}

AliasDialog::~AliasDialog(){
	delete mAliasesUi;
}
QRect AliasDialog::mAnimationRectRead() const { return mAnimationRect; }
void AliasDialog::mAnimationRectWrite(const QRect& rect) { mAnimationRect = rect; }
void AliasDialog::deleteRow(){
	int  row = mAliasesUi->aliasesTable->currentRow();

	if (!(mAliasesUi->aliasesTable->item(row, 0) && mAliasesUi->aliasesTable->item(row, 1)))
		return;
	mTempMap.erase(mAliasesUi->aliasesTable->item(row, 0)->text());//remove from map
	
	auto item1 = mAliasesUi->aliasesTable->item(row, 0);//first cell
	item1->setSelected(false);
	item1->setBackgroundColor(QColor(255, 206, 206));

	auto item2 = mAliasesUi->aliasesTable->item(row, 1);//second cell
	item2->setSelected(false);
	item2->setBackgroundColor(QColor(255, 206, 206));

	rowAnimation(mAliasesUi->aliasesTable, row,
	mAliasesUi->aliasesTable->rowHeight(mAliasesUi->aliasesTable->currentRow()), 0);//from row height to 0
}
void AliasDialog::dataChange(const QModelIndex & index, const QModelIndex&, const QVector<int> & roles){
	if (std::find(roles.begin(), roles.end(), Qt::EditRole) == roles.end())//find out why dataChanged was emited(only edit is accepted)
		return;
	if (mAliasesUi->aliasesTable->item(index.row(), 0)->text() != "" && mAliasesUi->aliasesTable->item(index.row(), 1)->text() != "") {//if new selection is not empty
		if (index.column() == 0) {//if we changing name
			auto tempValue = mTempMap[mPreviousKey];
			mTempMap.erase(mPreviousKey);
			mTempMap.insert({ mAliasesUi->aliasesTable->item(index.row(), index.column())->text(), tempValue });
		}
		else//if we changing value
			mTempMap[mAliasesUi->aliasesTable->item(index.row(), 0)->text()] = mAliasesUi->aliasesTable->item(index.row(), 1)->text();
	}
}
void AliasDialog::updateButtonGeometry() {
	int lastRowIndex = mAliasesUi->aliasesTable->rowCount() - 1;

	auto lastRowBottomY = mAliasesUi->aliasesTable->rowViewportPosition(lastRowIndex) + mAliasesUi->aliasesTable->rowHeight(lastRowIndex);

	mInsertRowButton->move(mAliasesUi->aliasesTable->rowCount() == 0? 0: -10 , 
											std::clamp(lastRowBottomY - mAliasesUi->aliasesTable->contentsMargins().bottom(), 0, mAliasesUi->aliasesTable->viewport()->height()));
	mAliasesUi->aliasesTable->viewport()->update();
}
void AliasDialog::insertRow() {
	int rowCount = mAliasesUi->aliasesTable->rowCount();

	mAliasesUi->aliasesTable->insertRow(rowCount);
	QTableWidgetItem* item1 = new QTableWidgetItem{ "" };
	item1->setBackgroundColor(QColor(208, 255, 206));

	QTableWidgetItem* item2 = new QTableWidgetItem{ "" };
	item2->setBackgroundColor(QColor(208, 255, 206));

	mAliasesUi->aliasesTable->setItem(rowCount, 0, item1);
	mAliasesUi->aliasesTable->setItem(rowCount, 1, item2);

	mAliasesUi->aliasesTable->setRowHeight(rowCount, 0);
	rowAnimation(mAliasesUi->aliasesTable, rowCount, 0, mAliasesUi->aliasesTable->verticalHeader()->defaultSectionSize());
}
void AliasDialog::resetColor(QTableWidgetItem* firstCell, QTableWidgetItem* secondCell){
	firstCell->setBackgroundColor(QColor(qRgba(255, 255, 255, 1)));
	secondCell->setBackgroundColor(QColor(qRgba(255, 255, 255, 1)));
}
void AliasDialog::setupTable() {	
	mAliasesUi->aliasesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mAliasesUi->aliasesTable->verticalHeader()->setMinimumSectionSize(1);

	mAliasesUi->aliasesTable->setColumnCount(2);
	mAliasesUi->aliasesTable->setRowCount(static_cast<int>(mTempMap.size()));

	mAliasesUi->aliasesTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Address")));
	mAliasesUi->aliasesTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Alias")));
	
	//populate the table with all the data
		int i{ 0 };
		for (const auto& [key, val] : mTempMap) {
			mAliasesUi->aliasesTable->setItem(i, 0, new QTableWidgetItem{ key });
			mAliasesUi->aliasesTable->setItem(i, 1, new QTableWidgetItem{ val });
			++i;
		}
		mAliasesUi->aliasesTable->setWhatsThis("Translates a specific IP address to a specified alias.\n" +
															  QString( "-Press the button in the last row to insert a new row.\n")+
																			  "-Delete/Backspace to delete selected row.");

		connect(mAliasesUi->aliasesTable, &QTableWidget::cellPressed, [&](int row, int column) mutable {
			mPreviousKey = mAliasesUi->aliasesTable->item(row, column)->text(); });
		connect(mAliasesUi->aliasesTable->model(), &QAbstractItemModel::dataChanged, this, &AliasDialog::dataChange);
}
void AliasDialog::setupButton() {
	mInsertRowButton = new QPushButton{ mAliasesUi->aliasesTable->viewport()};

	QGraphicsOpacityEffect opacity(mInsertRowButton);
	opacity.setOpacity(0.8);
	mInsertRowButton->setGraphicsEffect(&opacity);

	mInsertRowButton->setStyleSheet(QString{ "QPushButton{background-color: qlineargradient(spread: pad, x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 %1, stop: 1 %2);\
																				 border: 1px solid #e0e0e0;}\
																				QPushButton:pressed  {  border: 2px solid #a0a0a0; }" }
																				.arg(mInsertRowButton->palette().color(QPalette::Window).name())
																				.arg(mAliasesUi->aliasesTable->viewport()->palette().color(QPalette::Base).name()));


	mInsertRowButton->setFixedSize(mAliasesUi->aliasesTable->viewport()->width(), 30);
	mInsertRowButton->setWhatsThis("Press to insert new row in table");
	connect(this, &AliasDialog::updateButtonGeometryRequest, this, &AliasDialog::updateButtonGeometry);
	connect(mAliasesUi->aliasesTable->verticalHeader(), &QHeaderView::sectionResized, this, &AliasDialog::updateButtonGeometryRequest);
	connect(mInsertRowButton, &QPushButton::pressed, this, &AliasDialog::insertRow);
	connect(this, &AliasDialog::insertAnimationFinished, this, &AliasDialog::resetColor);

	emit updateButtonGeometryRequest();
	mInsertRowButton->show();
}
void AliasDialog::rowAnimation(QTableWidget* table, int row, int startValue, int endValue) {
	
	mAnim = new QPropertyAnimation{ this, "mAnimationRect" };
	mAnim->setEasingCurve(QEasingCurve::InOutQuad);
	mAnim->setDuration(25);

	mAnim->setStartValue(QRect{ 0, 0, 0, startValue });
	mAnim->setEndValue(QRect{ 0, 0, 0, endValue });

	connect(mAnim, &QPropertyAnimation::valueChanged, [&, table, row](const QVariant & value) {
		QRect rect = value.toRect();
		table->setRowHeight(row, rect.height());
		}
	);
	connect(mAnim, &QPropertyAnimation::finished, [&, this, table, row, startValue, endValue]() {
		if (startValue < endValue)
			emit insertAnimationFinished(table->item(row, 0), table->item(row, 1));
		else
			emit deleteAnimationFinished(table->item(row, 0), table->item(row, 1));
	});

	mAnim->start(QAbstractAnimation::DeleteWhenStopped);
	}
}