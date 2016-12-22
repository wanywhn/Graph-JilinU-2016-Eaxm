#include "graphlist.h"
#include <iostream>
#include <queue>
#include <time.h>
#include <vector>
#include <stddef.h>
GraphList::GraphList(int maxcity, int nadj) : realNumofCity(maxcity) {
  for (int i = 0; i != maxcity; i++) {
	Head[i].Adjcent = nullptr;
	first[i] = 1;
  }
  std::srand((unsigned int)time(NULL));
  std::vector<std::vector<int> > a(maxcity, std::vector<int>(maxcity));
  for (int i = 0; i != maxcity; i++) { // init
	for (int j = 0; j != maxcity; j++) {
	  a[i][j] = 0;
	}
  }
  for (int i = 0; i != nadj;) { // random get n
	int x = rand() % maxcity;
	int y = rand() % maxcity;
	if (a[x][y] == 0 && x != y) {
	  a[x][y] = 1;
	  i++;
	}
  }
  // Arr to List
  for (int i = 0; i != maxcity; i++) {
	for (int j = 0; j != maxcity; j++) {
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
		  for (; proc->next != nullptr && proc->info != i; proc = proc->next)
			;
		  if (proc->next == nullptr && proc->info != i) {
			proc->next = new Edge;
			proc->next->pre = proc;
			proc = proc->next;
			proc->dest = j;
			proc->info = i;
			proc->next = nullptr;
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
		  for (; proc->next != nullptr && proc->info != j; proc = proc->next)
			;
		  if (proc->next == nullptr && proc->info != j) {
			proc->next = new Edge;
			proc->next->pre = proc;
			proc = proc->next;
			proc->dest = i;
			proc->info = j;
			proc->next = nullptr;
		  }
		}
	  }
	}
  }
}

void GraphList::DFS(GraphList &tmp) {

  int status[realNumofCity]; //-1:being access,0:haven't,1:had
  for (int i = 0; i != realNumofCity; i++) {
	status[i] = 0;
  }

  Edge *proc = nullptr; // Find First Not Nullptr
  for (int i = 0; i != realNumofCity; i++) {
	if ((proc = Head[i].Adjcent) != nullptr) {
	  break;
	}
  }
  shuju rongyu;
  rongyu.end = -1;
  rongyu.start = -1;
  for (; proc != nullptr; proc = proc->next) {
	DFHelper(rongyu, proc, status);
	if(rongyu.start!=rongyu.end){
		//TODO
		}

  }
}

void GraphList::DFHelper(shuju &tmp, Edge *proc, int *a) {
  if (a[proc->info] == -1) {
	tmp.start = proc->dest;
	tmp.end = proc->info;
	std::cout << "Find rongyu" << std::endl;
	return;
  } else if (a[proc->info] == 0) {
	std::queue<Edge *> aque;
	Edge *ptr = Head[proc->info].Adjcent;
	for (; ptr != nullptr; ptr = ptr->next) {
	  aque.push(ptr);
	}
	a[proc->info] = -1;
	while (!aque.empty()) {
	  DFHelper(tmp, ptr, a);
	  ptr = aque.front();
	  aque.pop();
	}
	a[proc->info] = 1;
  } else {
	return;
  }
}
