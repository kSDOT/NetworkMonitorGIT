#pragma once
#include <QWidget>
#include  <QPropertyAnimation>
class QLineEdit;
namespace sta{
	class DrawerWidget : public QObject{
		Q_OBJECT
		Q_DISABLE_COPY(DrawerWidget)
	public:
		DrawerWidget(QWidget*, QObject* = nullptr);
		~DrawerWidget();
	
		Q_PROPERTY(QRect AnimationRect READ animationRectRead WRITE animationRectWrite)
		QRect animationRectRead() const;
		void animationRectWrite(const QRect&);
	signals:
		void maxRowsNumberChanged(int);
		void installFilter(const QString&);
	public slots:
		void openDrawer();
		void closeDrawer();
		std::vector<QLineEdit*> persistentLineEdits();
		void filterInstalled(const QString&);
		void clearFilter();
		void loadInitialSettings();//settings set progamatically
	private slots:
		void rowAnimation(const QRect&, const QRect&);
	private:
		void setupWidget();
	private:
		QRect mAnimationRect;
		QWidget& mWidget;
		QPropertyAnimation* mAnim;
	};
}