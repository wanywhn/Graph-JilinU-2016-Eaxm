#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define MAXNUMOFCITY 20
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
	
	
private:
	Adj Head[MAXNUMOFCITY];
	int realNumofCity;
	
};

#endif // GRAPHLIST_H
