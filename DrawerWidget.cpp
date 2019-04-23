#include "DrawerWidget.h"
#include <QColor>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include "ui_mainwindow.h"
namespace sta{

	DrawerWidget::DrawerWidget(QWidget* widget, QObject* parent) : QObject{ parent }, mWidget { *widget }{
		setupWidget();
	}
	DrawerWidget::~DrawerWidget(){}
	QRect DrawerWidget::animationRectRead() const{
		return mAnimationRect;
	}	
	void DrawerWidget::animationRectWrite(const QRect& rect) { 
		mAnimationRect = rect; 
	}
	void DrawerWidget::openDrawer() {
		rowAnimation(mWidget.geometry(), QRect{ mWidget.geometry().topRight() - QPoint{300 , 0},  mWidget.geometry().bottomRight() });
	}
	void DrawerWidget::closeDrawer() {
		rowAnimation( mWidget.geometry(),  QRect{mWidget.geometry().topRight(),  mWidget.geometry().bottomRight() });
	}
	std::vector<QLineEdit*> DrawerWidget::persistentLineEdits(){
		std::vector<QLineEdit*> vector;
		auto layout = mWidget.findChild<QGridLayout*>("gridLayout");
		for(int i = 0; i < layout->rowCount(); ++i)
			for (int j = 0; j < layout->columnCount(); ++j) {
				if (auto lineEdit = qobject_cast<QLineEdit*>(layout->itemAtPosition(i, j)->widget()); lineEdit != nullptr)
					vector.push_back(lineEdit);
		}
		return vector;
	}
	void DrawerWidget::filterInstalled(const QString& filter){
		auto layout = mWidget.findChild<QGridLayout*>("gridLayout");
		auto installedFiltersTextBrowser = qobject_cast<QTextBrowser*>(layout->itemAtPosition(2, 1)->widget());//installed filters
		installedFiltersTextBrowser->append(filter);
	}
	void DrawerWidget::clearFilter(){
		auto layout = mWidget.findChild<QGridLayout*>("gridLayout");
		auto installedFiltersTextBrowser = qobject_cast<QTextBrowser*>(layout->itemAtPosition(2, 1)->widget());//installed filters
		installedFiltersTextBrowser->clear();
	}
	void DrawerWidget::loadInitialSettings(){
		auto layout = mWidget.findChild<QGridLayout*>("gridLayout");
		auto maxRowsLineEdit = qobject_cast<QLineEdit*>(layout->itemAtPosition(0, 1)->widget());//textEdit
		emit maxRowsNumberChanged(maxRowsLineEdit->text().toInt());
	}
	void DrawerWidget::rowAnimation(const QRect& startRect, const QRect& endRect) {
		mWidget.setVisible(true);
		mAnim = new QPropertyAnimation{ this, "AnimationRect" };
		mAnim->setEasingCurve(QEasingCurve::InOutQuad);
		mAnim->setDuration(50);

		mAnim->setStartValue(startRect);
		mAnim->setEndValue(endRect);

		connect(mAnim, &QPropertyAnimation::valueChanged, [this](const QVariant & value) {
			QRect rect = value.toRect();
			mWidget.setMinimumWidth(rect.width());
			}
		);
		connect(mAnim, &QPropertyAnimation::finished, [this, startRect, endRect]() { this->mWidget.setVisible(startRect.width() < endRect.width()); });
		mAnim->start(QAbstractAnimation::DeleteWhenStopped);
		}
	void DrawerWidget::setupWidget(){
		mWidget.setStyleSheet(QString{ "QWidget{background-color: qlineargradient(spread: pad, x1: 1, y1: 0.5, x2: 0, y2: 0.5, stop: 0 %1, stop: 1 %2,);\
																				 border: 1px solid #e0e0e0;}" }
		.arg(QColor::fromRgb(230, 230, 230).name())
		.arg(QColor::fromRgb(245, 245, 245).name()));
		mWidget.setVisible(false);
		auto layout = mWidget.findChild<QGridLayout*>("gridLayout");
		auto maxRowsLineEdit = qobject_cast<QLineEdit*>(layout->itemAtPosition(0, 1)->widget());//textEdit
		maxRowsLineEdit->setValidator(new QIntValidator(1, 2147483647, maxRowsLineEdit));
		connect(maxRowsLineEdit, &QLineEdit::editingFinished, [this, maxRowsLineEdit]() {
			emit maxRowsNumberChanged(maxRowsLineEdit->text().toInt()); 
		});
		connect(maxRowsLineEdit, &QLineEdit::editingFinished, [this, maxRowsLineEdit]() {
			emit maxRowsNumberChanged(maxRowsLineEdit->text().toInt());
			});

		auto setFilterLineEdit = qobject_cast<QLineEdit*>(layout->itemAtPosition(1, 1)->widget());//filter line edit
		connect(setFilterLineEdit, &QLineEdit::returnPressed, [this, setFilterLineEdit]() {
			emit installFilter(setFilterLineEdit->text());
			setFilterLineEdit->clear(); }
		);	
	}
}