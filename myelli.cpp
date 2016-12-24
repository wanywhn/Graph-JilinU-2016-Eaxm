#include "myelli.h"

Myelli::Myelli(QString s, const Adj* h, QList<QPoint>* ry)
	: messg(s)
	, head(h)
	, rongyu(ry)
	, outflag(0)

{
	setToolTip(QString("城市") + messg);
	color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

QRectF Myelli::boundingRect() const
{
	qreal adjust = 0.5;
	return QRectF(-banjin / 2 - adjust, -banjin / 2 - adjust, banjin + adjust,
		banjin + adjust);
}

void Myelli::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
	QWidget* widget)
{
	Q_UNUSED(option);Q_UNUSED(widget);
	painter->setBrush(color);
	for (int i = 0; i != qGIL.size(); i++) { //!!!!!!!!
		if (outflag == 31) {
			painter->drawEllipse(-banjin / 2, -banjin / 2, banjin, banjin);
			if (((!Zengtian->empty()) && Zengtian->contains(this->messg.toInt()))) {
				painter->setBrush(Qt::green);
				painter->drawText(-banjin , 0, QString("添加交换机:") + messg);
			} else
				painter->drawText(-banjin * 3 / 8, 0, QString("城市") + messg);

		} else if (outflag == 32) {

		} else if (outflag == 21) {
			if (KeKao && ((KeKao->contains(QPoint(this->messg.toInt(),
							  qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt())))
							 || KeKao->contains(QPoint(qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt(), this->messg.toInt())))) {
				painter->setPen((Qt::green));

			} else {
				painter->setPen(Qt::darkRed);
			}
			painter->drawLine(QPointF(0, 0), mapFromParent(qGIL[i]->pos()));
			painter->drawEllipse(-banjin / 2, -banjin / 2, banjin, banjin);
			painter->drawText(-banjin * 3 / 8, 0, QString("城市") + messg);

		} else if (outflag == 0) {

			painter->setPen(Qt::red);
			if (((!rongyu->empty()) && rongyu->contains(QPoint(this->messg.toInt(), qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt()))) || rongyu->contains(QPoint(qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt(), this->messg.toInt()))) { // rongyu

				painter->setPen(Qt::black);
				painter->setPen(Qt::DotLine);
			}
			painter->drawLine(QPointF(0, 0), mapFromParent(qGIL[i]->pos()));
			painter->setPen(Qt::white);
			painter->drawEllipse(-banjin / 2, -banjin / 2, banjin, banjin);
			painter->setPen(Qt::black);
			painter->drawText(-banjin * 3 / 8, 0, QString("城市") + messg);
		} else if (outflag == 1 || outflag == 2) { // 1:zhicheng
			if (((!rongyu->empty()) && rongyu->contains(QPoint(this->messg.toInt(), qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt()))) || rongyu->contains(QPoint(qgraphicsitem_cast<Myelli*>(qGIL[i])->GetCity().toInt(), this->messg.toInt()))) { // rongyu
				{
					if (outflag == 1)
						painter->setPen(Qt::white);
					else
						painter->setPen(Qt::DotLine);
				}
			} else {
				painter->drawLine(QPointF(0, 0), mapFromParent(qGIL[i]->pos()));
				if (outflag == 1)
					painter->setPen(Qt::red);
				else
					painter->setPen(Qt::white);
			}
			painter->drawLine(QPointF(0, 0), mapFromParent(qGIL[i]->pos()));
			painter->setPen(color);
			painter->drawEllipse(-banjin / 2, -banjin / 2, banjin, banjin);
			painter->setPen(color);
			painter->drawText(-banjin * 3 / 8, 0, QString("城市") + messg);
		}
	}
}

void Myelli::SetMessg(QString s) { messg = s; }

void Myelli::SetBanjing(qreal r) { banjin = r; }

void Myelli::AddQGIL(QGraphicsItem* additem) { qGIL.append(additem); }

const QString& Myelli::GetCity() { return messg; }

void Myelli::setOutFlag(int x)
{
	outflag = x;
	// 0 Normal DisPlay
}

void Myelli::SetKeKao(QList<QPoint>* a)
{
	KeKao = a;
}

void Myelli::SetZengTian(QList<int>* p)
{
	Zengtian = p;
}

void Myelli::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	} else {
		setCursor(Qt::ClosedHandCursor);
	}
}

void Myelli::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	this->setPos(event->scenePos());
	// this->update();
}

void Myelli::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

	setCursor(Qt::OpenHandCursor);
	this->setPos(event->scenePos());
}
