#include "widget.h"
#include "graphlist.h"
#include "myelli.h"
#include "ui_widget.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QLineF>
#include <QMessageBox>
#include <QPointF>
#include <QString>
#include <QTime>
#include <QtMath>
Widget::Widget(QWidget *parent)
	: QWidget(parent), ui(new Ui::Widget), graph(nullptr) {
  ui->setupUi(this);
  ui->lineEdit_city->setValidator(new QIntValidator(2, 99, this));
  ui->lineEdit_line->setValidator(new QIntValidator(1, 200, this));
}

Widget::~Widget() {
  delete ui;
  if (graph)
	delete graph;
}
// Sheng cheng an niu
void Widget::on_pushButton_shengcheng_clicked() {
  if (ui->lineEdit_city->text().isEmpty() ||
	  ui->lineEdit_line->text().isEmpty()) {
	QMessageBox::critical(this, tr("错误！"), tr("请输入数据"));
  } else if (wcity > wline + 1) { // wu fa gou cheng
	QMessageBox::critical(this, tr("错误！"),
						  tr("城市联通线必须大于等于城市数减一"));
	return;
  } else {
	if (!graph) { // yi jing cun zai
	  graph = new GraphList(wcity, wline);
	  if ((graph = new GraphList(wcity, wline)) != nullptr) {
		DrawGraphQ1();
	  } else
		QMessageBox::critical(this, tr("shibai"), tr("shibai"));
	} else {
	  QMessageBox::StandardButton sure = QMessageBox::warning(
		  this, tr("警告"), tr("已经生成了，确认重新生成？"),
		  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	  if (sure == QMessageBox::Yes) { // que ren shan chu
		delete graph;
		if ((graph = new GraphList(wcity, wline)) != nullptr) {
		  //QMessageBox::information(this, tr("成功"), tr("成功"));
		  DrawGraphQ1();
		} else
		  QMessageBox::critical(this, tr("shibai"), tr("shibai"));
	  } else { // bu zuo cao zuo
		return;
	  }
	}
  }
}

void Widget::on_lineEdit_city_textChanged(const QString &arg1) {
  wcity = arg1.toInt();
#ifdef QT_DEBUG
  qDebug() << wcity;
#endif
}

void Widget::on_lineEdit_line_textChanged(const QString &arg1) {
  wline = arg1.toInt();
#ifdef QT_DEBUG
  qDebug() << wline;
#endif
}

void Widget::DrawGraphQ1() {
  //QGraphicsScene *scene = new QGraphicsScene;
	myScene *scene=new myScene;



  const Adj &head = *graph->GetHead();
  QList<int> rongyu;
  QList<QPoint> &listry=*new QList<QPoint>;
  bool successFlag=true;
  try{
	graph->DFS(&rongyu);
  }
  catch(QString exception){
	  QMessageBox::warning(this,tr("捕获异常"),exception);
	  successFlag=false;
  }
  if(successFlag)
		QMessageBox::information(this, tr("成功"), tr("成功"));

	for(int i=0;i!=rongyu.size();i+=2){
		listry.append(QPoint(rongyu.at(i),rongyu.at(i+1)));
	}


  std::vector<std::vector<int>> arr(wcity, std::vector<int>(wcity));
  graph->ListToArr(arr);


  qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
  for (int i = wcity - 1; i != -1; i--) {
	Myelli *nelli = new Myelli(tr("%1").arg(i),&head,&listry);
	 nelli->setPos(qrand()% 700,qrand()% 700);
	 nelli->SetBanjing(40);
	while (!nelli->collidingItems().isEmpty()) {
	  nelli->moveBy(nelli->pos().x() + qrand() % 70,
					nelli->pos().y() + qrand() % 70 - 100);
	}
	scene->addItem(nelli);
  }
#ifdef QT_DEBUG
  qDebug() << "Items()";
  qDebug() << scene->items();
#endif

  for (int i = 0; i != wcity; i++) {
	for (int j = 0; j != wcity; j++) {
	  if (arr[i][j] == 1 || arr[j][i] == 1) {
		qgraphicsitem_cast<Myelli*>(scene->items().at(i))->AddQGIL(scene->items().at(j));
		qgraphicsitem_cast<Myelli*>(scene->items().at(j))->AddQGIL(scene->items().at(i));
	  }
	}
  }
  ui->graphicsView->setScene(scene);
  ui->graphicsView->show();
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void Widget::SetOutFlagStat(int s)
{

	QList<Myelli*> ql;
	for(int i=0;i!=ui->graphicsView->scene()->items().size();i++){
		QGraphicsItem* qgi=ui->graphicsView->scene()->items().at(i);
		ql.append(qgraphicsitem_cast<Myelli*>(qgi));
	}
	for(int i=0;i!=ql.size();i++){
		ql[i]->setOutFlag(s);
	}
	ui->graphicsView->scene()->update();
	ui->graphicsView->update();
}


void Widget::on_pushButton_zhichengshu_clicked()
{
	SetOutFlagStat(1);
}

void Widget::on_pushButton_rongyu_clicked()
{
	SetOutFlagStat(2);
}

void Widget::on_pushButton_init_clicked()
{
	SetOutFlagStat(0);
}
