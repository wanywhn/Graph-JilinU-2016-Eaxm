
#include "widget.h"
#include <QApplication>
int Myelli::count=0;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.show();
	return a.exec();
}
