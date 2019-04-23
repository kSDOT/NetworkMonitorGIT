#pragma once
#pragma region INCLUDES
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTime>
#include <QtCharts/QValueAxis>
#include <QEasingCurve>
#include <QtCharts/QAreaSeries>
#pragma endregion
namespace sta {
	class Chart : public QWidget{
		Q_OBJECT

	public:
		Chart(QWidget* = nullptr);
		~Chart();

	public slots:		
		void addPoint(int, QTime&);//adds new point to series
		QtCharts::QChartView& chartView() const;
		//resets the graph to default view  when adapter is changed
		void clearData();
	private://FUNCTIONS
		QtCharts::QChart* createLineChart();//creates the line chart
	private://DATA MEMBERS
		QtCharts::QChartView* mChartView;
		QtCharts::QChart* mChart;
		QtCharts::QLineSeries* mLowerSeries;
		QtCharts::QLineSeries* mUpperSeries;
		QtCharts::QAreaSeries* mSeries;

		qreal mMinXVal;//range for X axis
		qreal mMaxXVal;
		  
		qreal mMinYVal;//range for Y axis
		qreal mMaxYVal;

		qreal mNewMaxY; 

		QTime mLastTime;//store values of last point added
		qreal mLastValue;
		std::list<std::pair<int, qreal>> mTimeValuePairs;
	};
}

