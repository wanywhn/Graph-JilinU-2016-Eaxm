
#include "graphlist.h"
#include <iostream>
#define nullptr 0
using namespace std;
void GraphList::SetOne()
{
	for (int i = 0; i < realNumofCity; i++) {
		if (!((Head[i].Adjcent != nullptr) && ((Head[i].Adjcent->next) == nullptr)))
			Trans[i] = 1; // chu yejiedianwaijunxuyaojia
	}
	Display();
}

void GraphList::SetTwo()
{
	for (int i = 0; i < realNumofCity; i++) {
		low[i] = i;
		Edge* p = Head[i].Adjcent;
		while (p != nullptr) {
			if (low[i] > (p->info))
				low[i] = p->info;
			p = p->next;
		}

	} // xian ba mei ge bianchengliqizuixiaodedian

	Abstract();
	// chouxiangchushu anxuhaoshunxu
	for (int i = 0; i < realNumofCity; i++) {
		Edge* q = Head[i].Adjcent;
		while (q != nullptr) {
			if (i < (q->info))
				children[i]++;
			q = q->next;
		}
	} // tongjizijiediangeshu
	if (children[0] > 1)
		Trans[0] = 1; // jiang0chengshimorenweigenjiedian
	for (int i = realNumofCity - 1; i >= 0; i--) {
		Edge* t = Head[i].Adjcent;
		while (t != nullptr) {
			if (((t->info) > i) && (low[t->info] < low[i]))
				low[i] = low[t->info];
			t = t->next;
		} // zijiedianlianbiqixiaozejixuxiugai
    }
	for (int i = 1; i < realNumofCity; i++) {
		while (children[i] != 0) {
			bool flag = false;
			Edge* u = Head[i].Adjcent;
			while (u != nullptr) {
				if (((u->info) > i) && (low[u->info] <= i)) {
					flag = true;
					break;
				}
				u = u->next;
			}
			if (flag == true)
				Trans[i] = 1;
        }
	}
	Display();
}

void GraphList::Display()
{
	for (int i = 0; i < realNumofCity; i++) {
		if (Trans[i] == 1) {
			cout << i << "city should prepare another transfer" << endl;
		}
    }
}

void GraphList::Abstract()
{
	int* visited = new int(realNumofCity);
	for (int i = 0; i < realNumofCity; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < realNumofCity; ++i) {
		Edge* u = Head[i].Adjcent;
		Edge* t;
		while (u != nullptr) {
			RDFS(u->info, visited);
			if (u->next != nullptr) {
				t = u->next->next;
				if (visited[u->next->info] == 1) {
					DeleteEdge(i, u->next->info);
					u = t;
				} else {
					u = u->next;
				}
			}
		}
	}
}
void GraphList::RDFS(const int v, int* visited)
{
	visited[v] = 1;
	int w = GetFirstNeighbor(v);
	while (w != -1) {
		if (!visited[w])
			RDFS(w, visited);
		w = GetNextNeighbor(v, w);
	}
}
void GraphList::DeleteEdge(const int& v1, const int& v2) //删除一条边
{
	if ((v1 == -1) || (v2 == -1))
		return;
	if (v1 == v2)
		return;
	Edge* p = Head[v1].Adjcent;
	while (p != NULL) {
		if (p->info == v2) {
			Head[v1].Adjcent = p->next;
			delete p;
			p = Head[v1].Adjcent;
		} else {
			while (p->next != NULL) {
				if (p->next->info == v2) {
					Edge* q = p->next;
					p->next = q->next;
					delete q;
				}
			}
		}
		p = Head[v2].Adjcent;
		while (p != NULL) {
			if (p->info == v1) {
				Head[v2].Adjcent = p->next;
				delete p;
				p = Head[v2].Adjcent;
			} else {
				while (p->next != NULL) {
					if (p->next->info == v1) {
						Edge* q = p->next;
						p->next = q->next;
						delete q;
					}
				}
			}
        }
	}
}

int GraphList::GetFirstNeighbor(const int v)
{
	if (v == -1)
		return -1;
	Edge* p = Head[v].Adjcent;
	if (p != NULL)
		return p->info;
	else
		return -1;
}

void GraphList::WhoIsInHuiLu(QList<int>* qli)
{
	int id[2 * realNumofCity];
	int visited[realNumofCity];
	for (int i = 0; i != realNumofCity; i++) {
		low[i] = -1;
		visited[i]=0;
	}
	for (int i = 0; i != 2 * realNumofCity; i++) {
		id[i] = -1;
	}
	qiaoDFS(id, 0,low,visited, qli);
}
int GraphList::qiaoDFS(int* id, int u,int *low,int* counter, QList<int>* ql)
{
	static int root = u; //记录源点
	int children = 0; //记录子节点数目
	Edge* p = Head[u].Adjcent;
	if (p == NULL)
		return 0;
	id[u] = low[u] = (*counter)++; //初始化
	for (; p != NULL; p = p->next) {
		if (id[p->info] == -1) { // (u,v)为树边
			children++;
			id[p->info+realNumofCity] = u; ////fuqin
			qiaoDFS(id, p->info,low,counter,ql);
			low[u] = min(low[u], low[p->info]);
			if ( id[u] < low[p->info]) {
				ql->append(p->info);
				ql->append(u);
			}
		} else if (p->info != id[u + realNumofCity]) // (u,v)为回边
			low[u] = min(low[u], id[p->info]);
	} // end-for
}

int GraphList::GetNextNeighbor(const int v1, const int v2)
{
	if (v1 != -1 && v2 != -1) {
		Edge* p = Head[v1].Adjcent;
		while (p->info != v2 && p != NULL)
			p = p->next;
		if (p == NULL)
			return -1;
		p = p->next;
		if (p == NULL)
			return -1;
		return p->info;
	}
	return -1;
}
