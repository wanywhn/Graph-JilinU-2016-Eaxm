#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define MAXNUMOFCITY 20
typedef struct{
	int start;
	int end;
}shuju;
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
	void DFHelper(shuju& tmp,Edge* proc,int *a);
	Adj Head[MAXNUMOFCITY];
	int realNumofCity;
	int first[MAXNUMOFCITY];
	
};

#endif // GRAPHLIST_H
