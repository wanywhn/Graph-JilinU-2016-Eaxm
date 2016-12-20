#include <iostream>
#include "graphlist.h"

using namespace std;

const int realNumofCity=10;
int main(int argc, char *argv[])
{
	GraphList agraph(10,12);
	agraph.DFS(agraph);
	return 0;
}

