#ifndef QCOLORBAR_H
#define QCOLORBAR_H

#include <QWidget>
#include "ui_qcolorbar.h"

class QColorBar : public QWidget
{
	Q_OBJECT

public:
	QColorBar(QWidget *parent = 0);
	~QColorBar();
	void paintEvent(QPaintEvent *e);

	int colorNum;
	double minValue, maxValue;
	std::vector<QColor> colorList;
	int startY;
	int mHeight;
private:
	Ui::QColorBar ui;
};

#endif // QCOLORBAR_H
