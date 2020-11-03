#include "Graph.hpp"



int main() {
	Graph<int> graph;

	graph.addNodeCpy(1, {0}, {2,3})
		.addNodeCpy(3, {}, {1});


	auto printValue{ 
		[](const int& v) {
			std::cout << v << " -> ";
		} 
	};

	std::cout << "=== ADJ LIST ===\n\n";
	graph.print();

	std::cout << "\n\n=== DFS ===\n\n";
	graph.depthFirstSearch(0, printValue);
	
	std::cout << "\n\n=== BFS ===\n\n";
	graph.breathFirstSearch(0, printValue);
	
	
	
	return 0;
}