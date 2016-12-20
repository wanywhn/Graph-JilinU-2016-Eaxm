#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define MAXNUMOFCITY 20
#include <queue>
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
	void DFS(GraphList &tmp);
	
	
private:
	void DFHelper(std::queue<int> &rongyu, Edge* proc, int *status);
	Adj Head[MAXNUMOFCITY];
	int realNumofCity;
	int first[MAXNUMOFCITY];
	int NumofEdge;
	
};

#endif // GRAPHLIST_H
