#include "visualization.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Visualization w;
	w.show();
	return a.exec();
}
