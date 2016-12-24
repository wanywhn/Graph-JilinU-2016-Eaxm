#include "myscene.h"

myScene::myScene()
{
}

void myScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
	event->accept();
}

void myScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	Q_UNUSED(event);
}

