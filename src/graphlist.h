#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define MAXNUMOFCITY 200
#include <queue>
#include <QList>
#include <QString>
#include <QQueue>
#include<QEvent>
#include<QFile>
typedef  struct GraphNode{
	int info;
	int dest;
	struct GraphNode* next;
	struct GraphNode* pre;
}Edge;

typedef struct {
	Edge* Adjcent;

}Adj;

class GraphList
{
public:
	GraphList(int maxcity,int nadj);//m,n
	~GraphList();
	const Adj *GetHead();
   
	void DFS(QList<int>*rongyulist=nullptr);
	
	void ListToArr(std::vector<std::vector<int> >&a);
	void ArrToList(std::vector<std::vector<int> >&a);
	void WhoIsInHuiLu(QList<int> *qli,int mode=0);
	void qiaoDFS(int * id , int u, int *low, int *counter, QList<int> *ql,int mode=0);
private:
	void DFHelper(std::queue<int> &rongyu, Edge* proc, int *status);
	int realNumofCity;
	int NumofEdge;
	int first[MAXNUMOFCITY];
	Adj Head[MAXNUMOFCITY];
	int low[MAXNUMOFCITY];         //quanbuchushiwei0
};

#endif // GRAPHLIST_H
