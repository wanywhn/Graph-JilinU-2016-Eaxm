#ifndef MYELLI_H
#define MYELLI_H

#include<QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <Qt>
#include <QtWidgets>
#include<QDropEvent>
#include <QLineF>
#include<QList>
#include<QPainter>
#include"graphlist.h"
#include<QObject>
class Myelli:public QGraphicsItem
{
public:
	explicit Myelli(QString s,const Adj *h,QList<QPoint> *ry);

	~Myelli();
	QRectF boundingRect() const ;
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem* option,QWidget *widget);
	void SetMessg(QString s);
	void SetBanjing(qreal r);
	void AddQGIL(QGraphicsItem*additem);
	const QString &GetCity();
	void setOutFlag(int x=0);
	void SetKeKao(QList<QPoint>*a);
	void SetZengTian(QList<int>* p);
private:
	static int count;
	QString messg;
	qreal banjin;
	QColor color;
	QList<QGraphicsItem*> qGIL;
	const Adj *head;
	QList<QPoint>* KeKao;
	QList<QPoint>* rongyu;
	int outflag;
	QList<int>* Zengtian;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

};

#endif // MYELLI_H
