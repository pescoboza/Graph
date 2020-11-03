#include "Graph.hpp"



int main() {
	Graph<int> graph;

	graph.addNodeCpy(6, { 5 }, {7,8})
		.addNodeCpy(5, { 6, 4, 1, 2 }, {7,10});

	graph.print();
	return 0;
}