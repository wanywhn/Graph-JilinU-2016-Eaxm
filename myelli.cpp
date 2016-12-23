#include "myelli.h"

Myelli::Myelli(QString s, const Adj *h, QList<QPoint> *ry)
	: messg(s), head(h), rongyu(ry), outflag(0)

{
  setToolTip(QString("城市") + messg);
  color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
}

QRectF Myelli::boundingRect() const {
  qreal adjust = 0.5;
  return QRectF(-banjin / 2 - adjust, -banjin / 2 - adjust, banjin + adjust,
				banjin + adjust);
}

void Myelli::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
				   QWidget *widget) {

  painter->setBrush(color);
  painter->drawEllipse(-banjin / 2, -banjin / 2, banjin, banjin);
  painter->drawText(-banjin * 3 / 8, 0, QString("城市") + messg);
  for (int i = 0; i != qGIL.size(); i++) { //!!!!!!!!
	if (outflag == 31) {
	  if (1) {

	  } else {
	  }

	} else if (((!rongyu->empty()) &&
				rongyu->contains(QPoint(this->messg.toInt(),
				qgraphicsitem_cast<Myelli *>(qGIL[i])->GetCity().toInt()))) ||
	rongyu->contains(QPoint(qgraphicsitem_cast<Myelli *>(qGIL[i])->GetCity().toInt(), this->messg.toInt()))) { // rongyu
	  if (outflag == 0 || outflag == 2) {
		painter->setPen(Qt::DotLine);
	  } else if (outflag == 1) {
		painter->setPen(Qt::white);
	  }

	} else { // zhicheng
	  painter->setPen(Qt::SolidLine);
	  if (outflag == 0 || outflag == 1) {
		painter->setPen(Qt::darkRed);
	  } else if (outflag == 2) {
		painter->setPen(Qt::white);
	  }
	}
	painter->drawLine(QPointF(0, 0), mapFromParent(qGIL[i]->pos()));
  }
}

void Myelli::SetMessg(QString s) { messg = s; }

void Myelli::SetBanjing(qreal r) { banjin = r; }

void Myelli::AddQGIL(QGraphicsItem *additem) { qGIL.append(additem); }

const QString &Myelli::GetCity() { return messg; }

void Myelli::setOutFlag(int x) {
  outflag = x;
  // 0 Normal DisPlay
}

void Myelli::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() != Qt::LeftButton) {
	event->ignore();
	return;
  } else {
	setCursor(Qt::ClosedHandCursor);
  }
}

void Myelli::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  this->setPos(event->scenePos());
  // this->update();
}

void Myelli::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

  setCursor(Qt::OpenHandCursor);
  this->setPos(event->scenePos());
}
