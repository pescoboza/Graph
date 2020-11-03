#include "Graph.hpp"



int main() {
	Graph<int> graph;

	graph.addNodeCpy(6, { 5 }, {7,8})
		.addNodeCpy(5, { 6, 4, 1, 2 }, {7,10});

	graph.depthFirstSearch(6, [](const int& value) {std::cout << value << " -> "; });
	std::cout << '\n';

	graph.print();
	return 0;
}