#pragma once
#pragma region INCLUDES
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTime>
#include <QtCharts/QValueAxis>
#pragma endregion
namespace sta {
	class Chart : public QWidget{
		Q_OBJECT

	public:
		Chart(QWidget* = nullptr);
		~Chart();
		
		void addPoint(int, QTime&);//adds new point to series
		QtCharts::QChartView& chartView() { return *mChartView; }

	public slots:
		//resets the graph to default view  when adapter is changed
		inline void clearData() { this->mSeries->clear(); mMaxYVal = 100; }
	private:
#pragma region FUNCTIONS
		QtCharts::QChart* createLineChart();//creates the line chart
#pragma endregion
#pragma region DATA MEMBERS
		QtCharts::QChartView* mChartView;
		QtCharts::QChart* mChart;
		QtCharts::QLineSeries* mSeries;

		int mMinXVal;//range for X axis
		int mMaxXVal;
		  
		int mMinYVal;//range for Y axis
		int mMaxYVal;

		QTime lastTime;//store values of last point added
		int lastLength;
#pragma endregion
	};
}

