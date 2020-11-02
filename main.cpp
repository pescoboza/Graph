#include "Graph.hpp"



int main() {
	Graph<int> graph;
	std::vector<int> parents{};
	std::vector<int> children{7,8};

	graph.addNode(6, parents, children);
	return 0;
}