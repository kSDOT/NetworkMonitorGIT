#include "chart.h"
namespace sta {
	Chart::Chart(QWidget* parent) : QWidget{ parent }, mMinXVal{ 0 }, mMaxXVal{ 60 }, mMinYVal{ 0 }, mMaxYVal{100},
	lastTime{ QTime::currentTime() }, lastLength{ 0 } {
		mChartView = new QtCharts::QChartView(createLineChart());//create chartview, antialiased and with horizontal zoom enabled
		mChartView->setRenderHint(QPainter::Antialiasing, true);
		mChartView->setRubberBand(QtCharts::QChartView::HorizontalRubberBand);
}												   
	Chart::~Chart(){
		delete mChartView;
		//mseries and mchart are set to have  mchartview  as parent
	}
	void Chart::addPoint(int length, QTime& time) {
		qreal timeSecMSec = time.second() + time.msec() / 1000;//get time  inf format sec.msec

		if ( time.minute() > lastTime.minute()) {//if the new point is in a new minute we reset the series
			mSeries->clear();
			mSeries->append(QPointF{ 0, static_cast<qreal>(lastLength)});
			mMaxYVal = lastLength;
			mChart->axisY()->setRange(mMinYVal, mMaxYVal);
		}

		lastTime = time;
		lastLength = length;
		mSeries->append(QPointF{ timeSecMSec, static_cast<qreal>(length) });

		if (qreal difference = length - mMaxYVal; difference > 0) {//resizes the y axis according to max Y value in axis
			mMaxYVal = length;
			mChart->axisY()->setRange(mMinYVal, mMaxYVal);
		}

	}
	QtCharts::QChart* Chart::createLineChart() {
		mChart = new QtCharts::QChart();//create and configure a new chart 
		mChart->setTitle("Data usage");
		mChart->setTitleFont(QFont{"Arial", 10});
		mChart->setTitleBrush(QBrush(Qt::black));
		mChart->legend()->hide();

		mSeries = new QtCharts::QLineSeries(mChart);//create a new series and add to chart
		mChart->addSeries(mSeries);

		mChart->createDefaultAxes();//configure axes
		reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisX())->setTickCount(16);
		reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisY())->setTickCount(5);
		
		mChart->axisX()->setRange(mMinXVal, mMaxXVal);
		mChart->axisY()->setRange(mMinYVal, mMaxYVal);

		reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisX())->setLabelFormat("%d");
		reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisY())->setLabelFormat("%d");

		mChart->axisX()->setGridLineVisible(false);

		return mChart;
	}
}