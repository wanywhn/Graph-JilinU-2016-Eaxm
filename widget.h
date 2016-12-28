#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "graphlist.h"
#include "myelli.h"
#include"myscene.h"
#include<QFile>
namespace Ui {
	class Widget;
	}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private slots:

	void on_lineEdit_city_textChanged(const QString &arg1);

	void on_lineEdit_line_textChanged(const QString &arg1);

	void on_pushButton_shengcheng_clicked();

	void on_pushButton_zhichengshu_clicked();

	void on_pushButton_rongyu_clicked();

	void on_pushButton_init_clicked();

	void on_pushButton_3_1_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::Widget *ui;
	GraphList *graph;
	myScene *scene;
	int wcity;int wline;
	void DrawGraphQ1();
	void SetOutFlagStat(int s, QList<QPoint>* a=nullptr);
	void SetOutFlagStat(int s,QList<int>*p);

};

#endif // WIDGET_H
