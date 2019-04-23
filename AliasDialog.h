#pragma once
#include <QTableWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QKeyEvent>
#include "ui_aliases.h"
class MainWindow;
namespace sta {
	class AliasDialog : public QWidget {
		Q_OBJECT
		Q_DISABLE_COPY(AliasDialog)
	public:
		AliasDialog(MainWindow* parent);
		~AliasDialog();

		Q_PROPERTY(QRect mAnimationRect READ mAnimationRectRead WRITE mAnimationRectWrite)
		QRect mAnimationRectRead() const;
		void mAnimationRectWrite(const QRect& rect);
	signals:
		void deleteAnimationFinished(QTableWidgetItem*, QTableWidgetItem*);
		void insertAnimationFinished(QTableWidgetItem*, QTableWidgetItem*);
		void updateButtonGeometryRequest();

	private slots:
		void deleteRow();
		void dataChange(const QModelIndex&, const QModelIndex&, const QVector<int>&);
		void updateButtonGeometry();
		void insertRow();
		void resetColor(QTableWidgetItem*, QTableWidgetItem*);
	private:
		void setupTable();
		void setupButton();
		void rowAnimation(QTableWidget*, int, int, int);
	private:
		QDialog* mAliases;
		Ui_aliasesDialog* mAliasesUi;
		QPushButton* mInsertRowButton;
		std::map<QString, QString> mTempMap;
		QString mPreviousKey;
		QRect mAnimationRect;
		QPropertyAnimation* mAnim =  nullptr;
	};

	class KeyPressEventFilter : public QObject {
		Q_OBJECT
	public:
		explicit KeyPressEventFilter(QObject* parent = nullptr) : QObject{ parent } {}
	signals:
		void keyDeleteRow();
		void enterCell();
	protected:
		bool eventFilter(QObject*, QEvent* event) override {
			if (event->type() == QEvent::KeyPress) {
				QKeyEvent* key = static_cast<QKeyEvent*>(event);
				if ((key->key() == Qt::Key_Delete) || (key->key() == Qt::Key_Backspace))
					emit keyDeleteRow();
				else if ((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return))
					emit enterCell();

				return true;
			}
			return false;
		}

	};
}