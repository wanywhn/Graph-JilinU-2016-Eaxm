#ifndef MYSCENE_H
#define MYSCENE_H

#include<QGraphicsScene>
#include<QGraphicsSceneDragDropEvent>

class myScene:public QGraphicsScene
{
public:
	myScene();
	void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
	void dropEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // MYSCENE_H
