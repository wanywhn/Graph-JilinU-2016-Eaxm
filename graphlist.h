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
    void SetOne();    //jiaru
    void SetTwo();    //jiaru
    void Display();   //jiaru
    void Abstract();  //jiaru
    void RDFS(const int v,int*visited); //jiaru
    void DeleteEdge(const int &v1,const int &v2);   //jiaru
    int  GetNextNeighbor(const int v1,const int v2);//jiaru
    int GetFirstNeighbor(const int v) ;     //jiaru
private:
	Adj Head[MAXNUMOFCITY];
    int Trans[MAXNUMOFCITY];   //quanbuchushiwei0
    int realNumofCity;
    int children[MAXNUMOFCITY];  //quanbuchushiwei0
    int low[MAXNUMOFCITY];         //quanbuchushiwei0


};

#endif // GRAPHLIST_H
