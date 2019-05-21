#include "chart.h"
#include "QTime"

namespace sta {
	Chart::Chart(QWidget* parent) : QWidget{ parent }, mMinXVal{ 0 }, mMaxXVal{ 10 }, mMinYVal{ 0 }, mMaxYVal{10},
	mLastTime{ QTime::currentTime() }{
		mChartView = new QtCharts::QChartView(createLineChart());//create chartview, antialiased and with horizontal zoom enabled
		mChartView->setRenderHint(QPainter::Antialiasing, true);
		mChartView->setRubberBand(QtCharts::QChartView::NoRubberBand);
		mChart->setAnimationEasingCurve(QEasingCurve::InOutQuad);
}												   
	Chart::~Chart(){
		delete mChartView;
		//mseries and mchart are set to have  mchartview  as parent
	}
	void Chart::addPoint(int lengthBytes, QTime& time) {
		qreal timeSecMSec = time.second() + time.msec() / 1000.0;//get time in format sec.msec
		qreal length = lengthBytes * 8.0 / 1024 / 1024;//display in MBit/s
		mLastValue = length;
		mTimeValuePairs.push_back({ time.second(), length });//keep the max value of last 6 sec
		mTimeValuePairs.remove_if([time](std::pair<int, qreal> pair) {return std::abs(pair.first - time.second()) > 6 && 
																														!(pair.first >= 50 && pair.second  >= 50); });

		mNewMaxY = 0; 
		std::for_each(mTimeValuePairs.begin(), mTimeValuePairs.end(), 
			[this](std::pair<int, qreal> pair) {if (this->mNewMaxY < pair.second) this->mNewMaxY = pair.second ; });

			if (mNewMaxY != mMaxYVal) {//resizes the y axis according to max Y value in axis
				mMaxYVal = std::max(1.0, mNewMaxY);//1 is the minimal displayable value
				mChart->axisY()->setRange(mMinYVal, mMaxYVal);
		    }

			if (timeSecMSec - 6 < 0)
				mChart->axisX()->setRange(0, 10);
			else if (timeSecMSec + 4 > 60)
				mChart->axisX()->setRange(50, 60);
			else
				mChart->axisX()->setRange(timeSecMSec - 6, timeSecMSec + 4);
			
			if(timeSecMSec < mLastTime.second() + mLastTime.msec() / 1000) {//if we go into a new minute
				mUpperSeries->clear();
				mLowerSeries->clear();
				mUpperSeries->append(0, mLastValue);
				mLowerSeries->append(0, 0);
			}

			mUpperSeries->append(QPointF{ timeSecMSec, std::max(0.025, length)});//make lines visible when height is 0
			mLowerSeries->append(QPointF{ timeSecMSec, 0});
			
			mLastTime = time;
	}
	QtCharts::QChartView& Chart::chartView() const{
		return *mChartView; 
	}
	void  Chart::clearData() {
		mUpperSeries->clear();
		mMaxYVal = 10; 
	}
	QtCharts::QChart* Chart::createLineChart(){
		mChart = new QtCharts::QChart();//create and configure a new chart 
		mChart->setTitle("Data usage");
		mChart->setTitleFont(QFont{"Arial", 10});
		mChart->setTitleBrush(QBrush(Qt::black));
		mChart->legend()->hide();

		
		mLowerSeries = new QtCharts::QLineSeries(mChart);
		mUpperSeries = new QtCharts::QLineSeries(mChart);
		mSeries = new QtCharts::QAreaSeries(mUpperSeries, mLowerSeries);//create a new series and add to chart
		mChart->addSeries(mSeries);

		mChart->createDefaultAxes();//configure axes
		QtCharts::QValueAxis* xAxis = reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisX());
		QtCharts::QValueAxis* yAxis = reinterpret_cast<QtCharts::QValueAxis*>(mChart->axisY());
		
		xAxis->setTickCount(11);
		xAxis->setRange(mMinXVal, mMaxXVal);
		xAxis->setLabelFormat("%.1f");
		xAxis->setGridLineVisible(false);
		
		yAxis->setTickCount(5);
		yAxis->setRange(mMinYVal, mMaxYVal);
		yAxis->setLabelFormat("%.4f");
		yAxis->setTitleText("Mb");
		
		return mChart;
	}
}