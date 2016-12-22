#include "graphlist.h"
#include "test.h"
#include <iostream>
#include <time.h>
#include <vector>
GraphList::GraphList(int maxcity, int nadj) : realNumofCity(maxcity) {
  for (int i = 0; i != maxcity; i++) {
    Head[i].Adjcent = nullptr;
  }
  std::srand((unsigned int)time(NULL));
  std::vector<std::vector<int>> a(maxcity, std::vector<int>(maxcity));
  for (int i = 0; i != maxcity; i++) { // init
    for (int j = 0; j != maxcity; j++) {
      a[i][j] = 0;
    }
  }
  for (int i = 0; i != nadj;) { // random get n
    int x = rand() % maxcity + 1;
    int y = rand() % maxcity + 1;
    if (a[x][y] == 0) {
      a[x][y] = 1;
      i++;
    }
  }
  // Arr to List
  for (int i = 0; i != maxcity; i++) {
    int first = true;
    for (int j = 0; j != maxcity; j++) {
      if (a[i][j] != 0) {
        Edge *proc;
        if (first) {
          Head[i].Adjcent = new Edge;
          Head[i].Adjcent->pre = nullptr;
          proc = Head[i].Adjcent;
        } else {
          proc = Head[i].Adjcent;
          for (; proc->next != nullptr; proc = proc->next)
            ;
          proc->next = new Edge;
          proc->next->pre = proc;
          proc = proc->next;
        }
        proc->dest = i;
        proc->info = j;
        proc->next = nullptr;
      }
    }
  }
}
