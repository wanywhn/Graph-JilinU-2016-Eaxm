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
	//event->acceptProposedAction();
	//for(int i=0;i!=this->items().size();i++)
	//sendEvent(this->items().at(i),event);
}

