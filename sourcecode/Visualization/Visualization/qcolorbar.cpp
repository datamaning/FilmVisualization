#include "qcolorbar.h"
#include "qpainter.h"
QColorBar::QColorBar(QWidget *parent)
	: QWidget(parent), minValue(0), maxValue(400), startY(450), mHeight(0)
{
	ui.setupUi(this);
	colorNum = 5;
	//默认颜色条
	QColor index1(0, 0, 255);
	QColor index2(0,255,255);
	QColor index3(255, 255, 0);
	QColor index4(255,150, 0);
	QColor index5(255, 0, 0);
	colorList.push_back(index1);
	colorList.push_back(index2);
	colorList.push_back(index3);
	colorList.push_back(index4);
	colorList.push_back(index5);
}

QColorBar::~QColorBar()
{

}
void QColorBar::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	// 左上角是原点
	int startX = 0, mWidth = 120;
	QRect rect(startX, startY, mWidth, mHeight);
	painter.setPen(QColor(255, 239, 239));
	QLinearGradient linearGradient(24,0,24,450);
	/*linearGradient.setColorAt(0, Qt::red);
	linearGradient.setColorAt(0.333, Qt::yellow);
	linearGradient.setColorAt(0.667, Qt::green);
	linearGradient.setColorAt(1, Qt::blue);*/
	for (int i=0; i<colorNum; i++)
	{
		double pos = (double)1.0 / (colorNum-1) * i;
		linearGradient.setColorAt( pos, colorList[colorNum-1-i]);
	}
	painter.setBrush(linearGradient);
	painter.drawRect(rect);

	painter.setPen(QColor(80, 80, 80));
	/*painter.setFont( QFont("lucida", 8, QFont::Bold) );*/
	double space = (maxValue - minValue) / colorNum;
	int textStartX = 130;
	int offsetY = 90;
	painter.drawText(textStartX, 10, QString::number((int)maxValue));
	painter.drawText(textStartX, 10 + offsetY, QString::number((int)(minValue + space * 4)));
	painter.drawText(textStartX, 10 + offsetY*2, QString::number((int)(minValue + space * 3)));
	painter.drawText(textStartX, 10 + offsetY * 3, QString::number((int)(minValue + space * 2)));
	painter.drawText(textStartX, 10 + offsetY * 4, QString::number((int)(minValue + space)));
	painter.drawText(textStartX, 10 + offsetY * 5, QString::number((int)minValue));
}