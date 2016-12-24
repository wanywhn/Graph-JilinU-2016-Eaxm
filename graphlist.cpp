#include "graphlist.h"
#include "test.cpp"
#include <QDebug>
#include <iostream>
#include <queue>
#include <time.h>
#include <vector>
#include<cstdlib>

GraphList::GraphList(int maxcity, int nadj)
	: realNumofCity(maxcity), NumofEdge(nadj) {
  for (int i = 0; i != maxcity; i++) {
	Head[i].Adjcent = nullptr;
	first[i] = 1; // Help Vect to List
  }
  std::srand((unsigned int)time(NULL));
  std::vector<std::vector<int> > a(maxcity, std::vector<int>(maxcity));
  for (int i = 0; i != maxcity; i++) { // init
    for (int j = 0; j != maxcity; j++) {
      a[i][j] = 0;
    }

  }

#ifndef DEBUG
  for (int i = 0; i != nadj;) { // random get n

	int x = rand() % maxcity;
	int y = rand() % maxcity;
	if (a[y][x] == 0 && a[x][y] == 0 && x != y) {
	  a[x][y] = 1;
	  i++;
	}

  }
#endif
#ifdef DEBUG
  a[0][8] = 1;
  a[0][9] = 1;
  a[1][9] = 1;
  a[1][3] = 1;
  a[2][6] = 1;
  a[2][7] = 1;
  a[3][4] = 1;
  a[3][6] = 1;
  a[3][8] = 1;
  a[3][9] = 1;
  a[5][9] = 1;
#endif
  ArrToList(a);
}

// Find Cricle
void GraphList::DFS(QList<int> *rongyulist) {

  int status[realNumofCity]; //-1:being accessed,0:haven't,1:had
  for (int i = 0; i != realNumofCity; i++) {
	status[i] = 0;
  }

  Edge *proc = nullptr; // Find First Not Nullptr
  for (int i = 0; i != realNumofCity; i++) {
	if ((proc = Head[i].Adjcent) != nullptr) {
	  break;
	}
  }
  std::queue<int> rongyu;
  for (; proc != nullptr; proc = proc->next) {
	DFHelper(rongyu, proc, status);
  }
  int sum = 0;
  for (int j = 0; j != realNumofCity; j++) {
	sum += status[j];
  }
  if (NumofEdge + 1 - rongyu.size() / 2 < realNumofCity) {
	std::cout << "fei lian tong tu" << std::endl;
	throw QString("无法构成连通图");
  }
  if (!rongyu.empty()) {
	while (!rongyu.empty()) {
	  rongyulist->push_back(rongyu.front());
#ifdef DEBUG
	std::cout << "rongyu:" << rongyu.front();
	rongyu.pop();

	std::cout << ',' << rongyu.front() << std::endl;
	  rongyulist->push_back(rongyu.front());
#endif
	  rongyu.pop();
	}
  }
}

const Adj *GraphList::GetHead() { return Head; }

void GraphList::DFHelper(std::queue<int> &rongyu, Edge *proc, int *status) {
  if (status[proc->info] == -1) {
	rongyu.push(proc->dest);
	rongyu.push(proc->info);
	std::cout << "Going to Visit " << proc->info << std::endl;
	std::cout << "Find rongyu:" << proc->dest << "," << proc->info << std::endl;
	return;
  } else if (status[proc->info] == 0) {
#ifdef DEBUG
	std::cout << "Going to Visit " << proc->info << std::endl;
#endif
	std::queue<Edge *> aque;
	status[proc->dest] =
		-1; // proc->dest is being visited,Now is visiting his chil
	Edge *ptr = Head[proc->info].Adjcent;
	for (; ptr != nullptr; ptr = ptr->next) {
	  if (ptr->info != proc->dest)
		aque.push(ptr);
	}

	if (aque.empty()) {
		status[proc->info]=1;
	  std::cout << proc->info << " Has Been Accessed Succefully" << std::endl;
	  return;
	} else {
	  ptr = aque.front();
#ifdef DEBUG
	  std::cout << "Going to Visit From " << proc->info << " " << std::endl;
#endif
	  while (!aque.empty()) {
		aque.pop();
		DFHelper(rongyu, ptr, status);
		ptr = aque.front();
	  }
	}
	status[proc->info] = 1;
	std::cout << proc->info << " Has Been Accessed Succefully" << std::endl;
#ifdef DEBUG
#endif
  } else {
	return;
  }
}

void GraphList::ArrToList(std::vector<std::vector<int>> &a) {
  // Vect to List
  for (int i = 0; i != realNumofCity; i++) {
	for (int j = 0; j != realNumofCity; j++) {
	  if (a[i][j] != 0) {
		// j-i
		Edge *proc;
		if (first[j]) {
		  Head[j].Adjcent = new Edge;
		  Head[j].Adjcent->pre = nullptr;
		  proc = Head[j].Adjcent;
		  first[j] = 0;
		  proc->dest = j;
		  proc->info = i;
		  proc->next = nullptr;
		} else {
		  proc = Head[j].Adjcent;
		  for (; proc->next != nullptr && proc->info < i; proc = proc->next)
			;
		  if (proc->info == i)
			break;
		  if (proc->next == nullptr && proc->info < i) {
			proc->next = new Edge;
			proc->next->pre = proc;
			proc = proc->next;
			proc->dest = j;
			proc->info = i;
			proc->next = nullptr;
		  } else if (proc->info > i) { // pro->info>i

			if (proc->pre == nullptr) {
			  Head[j].Adjcent = new Edge;
			  Head[j].Adjcent->next = proc;
			  proc->pre = Head[j].Adjcent;
			  proc->pre->info = i;
			  proc->pre->dest = j;
			} else { // proc->pre!=nullptr
			  proc->pre->next = new Edge;
			  proc->pre->next->info = i;
			  proc->pre->next->dest = j;
			  proc->pre->next->next = proc;
			  proc->pre = proc->pre->next;
			}
		  } else {
		  }
		}

		// i-j
		if (first[i]) {
		  Head[i].Adjcent = new Edge;
		  Head[i].Adjcent->pre = nullptr;
		  proc = Head[i].Adjcent;
		  first[i] = 0;
		  proc->dest = i;
		  proc->info = j;
		  proc->next = nullptr;
		} else {
		  proc = Head[i].Adjcent;
		  for (; proc->next != nullptr && proc->info < j; proc = proc->next)
			;
		  if (proc->info == j)
			break;
		  if (proc->next == nullptr &&
			  proc->info < j) { // hou wu ,qie xiao yu zhe ge
			proc->next = new Edge;
			proc->next->pre = proc;
			proc = proc->next;
			proc->dest = i;
			proc->info = j;
			proc->next = nullptr;
		  } else if (proc->info > j) {

			if (proc->pre == nullptr) { // hou wu qie da yu zhe ge
			  Head[i].Adjcent = new Edge;
			  Head[i].Adjcent->next = proc;
			  proc->pre = Head[i].Adjcent;
			  proc->pre->info = j;
			  proc->pre->dest = i;
			} else { // proc.next!=nullptr
			  proc->pre->next = new Edge;
			  proc->pre->next->info = j;
			  proc->pre->next->dest = i;
			  proc->pre->next->next = proc;
			  proc->pre = proc->pre->next;
			}
		  }
		}
	  }
	}
  }
}

void GraphList::ListToArr(std::vector<std::vector<int>> &a) {
  for (int i = 0; i != realNumofCity; i++) { // init
	for (int j = 0; j != realNumofCity; j++) {
	  a[i][j] = 0;
	}
  }
  for (int i = 0; i != realNumofCity; i++) {
	for (Edge *proc = Head[i].Adjcent; proc != nullptr; proc = proc->next) {
	  if (proc != nullptr) {
		a[i][proc->info] = 1;
	  }
	}
  }
}
