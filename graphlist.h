#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define MAXNUMOFCITY 20
#include <queue>
#include <QList>
#include <QString>
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
	void DFS(QList<int>*rongyulist=nullptr);
	const Adj *GetHead();
	void ListToArr(std::vector<std::vector<int>>&a);


private:
	void DFHelper(std::queue<int> &rongyu, Edge* proc, int *status);
	Adj Head[MAXNUMOFCITY];
	int realNumofCity;
	int first[MAXNUMOFCITY];
	int NumofEdge;
	void ArrToList(std::vector<std::vector<int>>&a);

};

#endif // GRAPHLIST_H
